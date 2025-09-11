#include "HTTPUtils.h"

struct ContinueException {};

std::optional<std::string> HTTPUtils::fetchPage(const Link& url, const Config& config) {
    Link currentUrl = url;
    int redirectCount = 0;
    
    while (redirectCount <= config.maxRedirects) {
        net::io_context ioc;
        
        try {            
            switch (currentUrl.protocol)
            {
            case ProtocolType::HTTPS:
                return handleHttps(ioc, currentUrl, redirectCount, config).value();
                break;
                
            case ProtocolType::HTTP:
                return handleHttp(ioc, currentUrl, redirectCount, config).value();
                break;
            
            default:
                break;
            }      
        
        } catch (const ContinueException&) {
            continue;  // handleHttp/s функция кидает исключение ловим и продолжаем дальше
        } catch (const std::exception& e) {
            std::cerr << "HTTP request failed for " << currentUrl.hostName << ": " << e.what() << std::endl;
            return std::nullopt;
        }
    }
    
    std::cerr << "Too many redirects (" << config.maxRedirects << ") for URL: " << url.link << std::endl;
    return std::nullopt;
}

bool HTTPUtils::isTextContent(const std::string& content) {
    if (content.empty()) return false;
    
    // Наличие нулевых байтов в первых 1024 символах (или во всем содержимом, если оно короче).
    size_t checkLength = std::min(content.length(), size_t(1024));
    for (size_t i = 0; i < checkLength; ++i) {
        if (content[i] == '\0') {
            return false;
        }
    }
    
    // Количество печатных символов
    size_t printableCount = 0;
    for (size_t i = 0; i < checkLength; ++i) {
        if (std::isprint(static_cast<unsigned char>(content[i])) || 
            std::isspace(static_cast<unsigned char>(content[i]))) {
            printableCount++;
        }
    }
    
    // Если не менее 95% символов читаемые, считать текстом
    return (printableCount * 100 / checkLength) >= 95;
}

bool HTTPUtils::isRedirectResponse(int statusCode)
{
    return statusCode == 301 || statusCode == 302 || statusCode == 303 || 
           statusCode == 307 || statusCode == 308;
}
 

std::optional<std::string> HTTPUtils::handleHttps(net::io_context& ioc, Link& currentUrl, int& redirectCount, const Config& config) {
    // HTTPS имплементация
    ssl::context ctx(ssl::context::tlsv12_client);
    
    if (config.verifySSL) {
        ctx.set_default_verify_paths();
        ctx.set_verify_mode(ssl::verify_peer);
    } else {
        ctx.set_verify_mode(ssl::verify_none);
    }
    
    beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);
    
    // SNI hostname
    if (!SSL_set_tlsext_host_name(stream.native_handle(), currentUrl.hostName.c_str())) {
        beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        std::cerr << "Failed to set SNI hostname: " << ec.message() << std::endl;
        return std::nullopt;
    }
    
    // Установка таймаута
    beast::get_lowest_layer(stream).expires_after(config.timeout);
    
    // Подключение
    tcp::resolver resolver(ioc);
    auto const results = resolver.resolve(currentUrl.hostName, "443");
    beast::get_lowest_layer(stream).connect(results);
    
    // SSL
    beast::error_code handshake_ec;
    stream.handshake(ssl::stream_base::client, handshake_ec);
    if (handshake_ec) {
        std::cerr << "SSL handshake failed: " << handshake_ec.message() << std::endl;
        return std::nullopt;
    }

    // HTTP запрос
    http::request<http::empty_body> req{http::verb::get, currentUrl.query, 11};
    req.set(http::field::host, currentUrl.hostName);
    req.set(http::field::user_agent, config.userAgent);
    req.set(http::field::connection, "close");
    
    // Отправка запроса
    beast::error_code write_ec;
    http::write(stream, req, write_ec);
    if (write_ec) {
        std::cerr << "Failed to write request: " << write_ec.message() << std::endl;
        return std::nullopt;
    }
    
    // Получение ответа
    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    beast::error_code read_ec;
    http::read(stream, buffer, res, read_ec);
    if (read_ec) {
        std::cerr << "Failed to read response: " << read_ec.message() << std::endl;
        return std::nullopt;
    }
    
    // Проверка редиректа
    auto redirectResult = handleRedirect(res, currentUrl, redirectCount, config);
    if (redirectResult.has_value()) {
        currentUrl = redirectResult.value();
        redirectCount++;
        
        // Выключаем поток и кидаем исключение чтоб продолжить следующий цикл while
        beast::error_code ec;
        stream.shutdown(ec);
        throw ContinueException {};
    }
    
    // Конвертация ответа в строку
    std::string content = beast::buffers_to_string(res.body().data());
    
    // Проверка что тект
    if (config.textOnly && !isTextContent(content)) {
        if (!config.relaxedTextDetection) {
            std::cerr << "Content is not text, skipping..." << std::endl;
            return std::nullopt;
        }
    }
    
    // Выключаем поток и выходим
    beast::error_code ec;
    stream.shutdown(ec);
    if (ec == net::error::eof) {
        ec = {};
    }
    
    return content;
}

std::optional<std::string> HTTPUtils::handleHttp(net::io_context& ioc, Link& currentUrl, int& redirectCount, const Config& config) {
    // HTTP имплементация
    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);
    
    // Задаем таймаут
    stream.expires_after(config.timeout);
    
    // Подключение
    auto const results = resolver.resolve(currentUrl.hostName, "80");
    stream.connect(results);
    
    // HTTP запрос
    http::request<http::empty_body> req{http::verb::get, currentUrl.query, 11};
    req.set(http::field::host, currentUrl.hostName);
    req.set(http::field::user_agent, config.userAgent);
    req.set(http::field::connection, "close");
    
    // Отправка запроса
    http::write(stream, req);
    
    // Получение ответа
    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(stream, buffer, res);
    
    // Проверка редиректа
    auto redirectResult = handleRedirect(res, currentUrl, redirectCount, config);
    if (redirectResult.has_value()) {
        currentUrl = redirectResult.value();
        redirectCount++;
        
        // Выключаем поток и кидаем исключение чтоб продолжить следующий цикл while
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);
        throw ContinueException {};
    }
    
    // Конвертация ответа в строку
    std::string content = beast::buffers_to_string(res.body().data());
    
    // Проверка что тект
    if (config.textOnly && !isTextContent(content)) {
        if (!config.relaxedTextDetection) {
            std::cerr << "Content is not text, skipping..." << std::endl;
            return std::nullopt;
        }
    }
    
    // Выключаем поток и выходим
    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);
    if (ec && ec != beast::errc::not_connected) {
        std::cerr << "Shutdown error: " << ec.message() << std::endl;
    }
    
    return content;
}

