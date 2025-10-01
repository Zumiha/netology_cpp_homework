#include "ServerHttpUtils.h"

std::unordered_map<std::string, std::string> ServerHttpUtils::parseQueryString(const std::string& query_str) {
    std::unordered_map<std::string, std::string> params;
    
    size_t start = 0;
    while (start < query_str.length()) {
        size_t amp_pos = query_str.find('&', start);
        size_t end = (amp_pos != std::string::npos) ? amp_pos : query_str.length();
        
        std::string pair = query_str.substr(start, end - start);
        size_t eq_pos = pair.find('=');
        
        if (eq_pos != std::string::npos) {
            std::string key = urlDecode(pair.substr(0, eq_pos));
            std::string value = urlDecode(pair.substr(eq_pos + 1));
            params[key] = value;
        }
        
        start = end + 1;
    }
    
    return params;
}

std::string ServerHttpUtils::urlDecode(const std::string& encoded) {
    std::string result;
    result.reserve(encoded.length());
    
    for (size_t i = 0; i < encoded.length(); ++i) {
        if (encoded[i] == '+') {
            result += ' ';
        }
        else if (encoded[i] == '%' && i + 2 < encoded.length()) {
            try {
                std::string hex = encoded.substr(i + 1, 2);
                char decoded_char = static_cast<char>(std::stoi(hex, nullptr, 16));
                result += decoded_char;
                i += 2;
            } catch (...) {
                result += encoded[i]; // Сохраняем оригинальный символ при ошибке
            }
        }
        else {
            result += encoded[i];
        }
    }
    
    return result;
}

std::string ServerHttpUtils::htmlEscape(const std::string& text) {
    std::string escaped;
    escaped.reserve(text.length() * 1.1);
    
    for (char c : text) {
        switch (c) {
            case '&':  escaped += "&amp;"; break;
            case '<':  escaped += "&lt;"; break;
            case '>':  escaped += "&gt;"; break;
            case '"':  escaped += "&quot;"; break;
            case '\'': escaped += "&#39;"; break;
            default:   escaped += c;
        }
    }
    
    return escaped;
}


std::string ResponseTemplates::buildSearchPage(const std::string& error_msg) {
    std::ostringstream html;
    
     html << R"(<!DOCTYPE html>
    <html>
        <head>
            <meta charset="UTF-8">
            <title>Search Engine</title>
        </head>
        <body>
        <h1>Search Engine</h1>
    )";
            
    if (!error_msg.empty()) {
        html << "    <p style=\"color: red;\"><strong>Error:</strong> " 
            << ServerHttpUtils::htmlEscape(error_msg) << "</p>\n";
    }
            
            html << R"(
            <form method="GET" action="/search">
                <label>Search query:</label>
                <input type="text" name="q" placeholder="Enter search terms" required />
                <label>Results limit:</label>
                <input type="number" name="limit" value="10" min="1" max="100" />
                <button type="submit">Search</button>
            </form>
        
            <hr>
            <h3>Instructions:</h3>
            <ul>
                <li>Enter words separated by spaces</li>
                <li>Pages are ranked by total word frequency</li>
                <li>Results are limited to the specified number</li>
            </ul>
        </body>
    </html>)";
        
    return html.str();
}

std::string ResponseTemplates::buildResultsPage(const std::string &query, const std::vector<DatabaseManager::RelevanceSearchResult> &results, int limit) {
    std::ostringstream html;
        
    html << R"(<!DOCTYPE html>
    <html>
        <head>
            <meta charset="UTF-8">
            <title>Search Results: )" << ServerHttpUtils::htmlEscape(query) << R"(</title>
        </head>
        <body>
            <h1>Search Results for: ")" << ServerHttpUtils::htmlEscape(query) << R"("</h1>
            <p>Found <strong>)" << results.size() << R"(</strong> result(s)</p>
            <p><a href="/">Back to Search</a></p>
            <hr>
        )";
                
                if (results.empty()) {
                    html << R"(
            <p><strong>No results found.</strong></p>
            <p>Try different search terms or check your spelling.</p>
        )";
                } else {
                    for (size_t i = 0; i < results.size(); ++i) {
                        const auto& result = results[i];
                        
                        html << "    <div style=\"margin-bottom: 30px;\">\n";
                        html << "        <h3>" << (i + 1) << ". <a href=\"" 
                            << ServerHttpUtils::htmlEscape(result.url) << "\" target=\"_blank\">" 
                            << ServerHttpUtils::htmlEscape(result.title) << "</a></h3>\n";
                        html << "        <p><strong>URL:</strong> " 
                            << ServerHttpUtils::htmlEscape(result.url) << "</p>\n";
                        html << "        <p><strong>Relevance Score:</strong> " 
                            << result.total_relevance << "</p>\n";
                        html << "        <p><strong>Page ID:</strong> " << result.page_id << "</p>\n";
                        
                        if (!result.word_frequencies.empty()) {
                            html << "        <p><strong>Word Frequencies:</strong> ";
                            for (size_t j = 0; j < result.word_frequencies.size(); ++j) {
                                if (j > 0) html << ", ";
                                html << ServerHttpUtils::htmlEscape(result.word_frequencies[j].first) 
                                    << " (" << result.word_frequencies[j].second << ")";
                            }
                            html << "</p>\n";
                        }
                        
                        html << "    </div>\n";
                    }
                }
                
                html << R"(
            <hr>
            <p><a href="/">New Search</a></p>
        </body>
    </html>)";
        
    return html.str();
}

std::string ResponseTemplates::build404Page() {
    return R"(<!DOCTYPE html>
    <html>
        <head>
            <meta charset="UTF-8">
            <title>404 - Not Found</title>
        </head>
        <body>
            <h1>404 - Page Not Found</h1>
            <p>The requested page does not exist.</p>
            <p><a href="/">Back to Search</a></p>
        </body>
    </html>)";
}

std::string ResponseTemplates::buildErrorPage(const std::string &error) {
    std::ostringstream html;
    html << R"(<!DOCTYPE html>
    <html>
        <head>
            <meta charset="UTF-8">
            <title>Server Error</title>
        </head>
        <body>
            <h1>Server Error</h1>
            <p>An error occurred while processing your request:</p>
            <pre>)" << ServerHttpUtils::htmlEscape(error) << R"(</pre>
            <p><a href="/">Back to Search</a></p>
        </body>
    </html>)";
    return html.str();
}

void HttpConnectionHandler::handle() {
    try {
        // Чтение HTTP-запроса от клиента (BLOCKS)
        beast::flat_buffer buffer;
        http::request<http::string_body> request;
        
        beast::error_code ec;
        http::read(socket_, buffer, request, ec);
        
        if (ec == http::error::end_of_stream) {
            return; // Клиент закрыл соединение
        }
        
        if (ec) {
            std::cerr << "Read error: " << ec.message() << std::endl;
            return;
        }
        
        // Логгируем запрос
        std::cout << "[" << request.method_string() << "] " 
                    << request.target() 
                    << " from " << socket_.remote_endpoint() << std::endl;
        
        // Обрабатываем и генерируем ответ
        auto response = processRequest(request);
        
        // Отправляем ответ (BLOCKS)
        http::write(socket_, response, ec);
        
        if (ec) {
            std::cerr << "Write error: " << ec.message() << std::endl;
        }
        
        // Плавное завершение работы
        socket_.shutdown(tcp::socket::shutdown_send, ec);
        
    } catch (const beast::system_error& e) {
        if (e.code() != http::error::end_of_stream) {
            std::cerr << "Beast error: " << e.what() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
    }
}

http::response<http::string_body> HttpConnectionHandler::processRequest(const http::request<http::string_body> &request) {
    std::string method = std::string(request.method_string());
    std::string target = std::string(request.target());
    
    // Направляем на разные обработчики в зависимости от метода и пути
    if (method == "GET") {
        if (target == "/" || target.empty()) {
            return serveSearchPage();
        } else if (target.starts_with("/search")) {
            return handleGetSearch(target);
        }
    } else if (method == "POST") {
        if (target == "/search") {
            return handlePostSearch(request.body());
        }
    }
    
    return serve404();
}

http::response<http::string_body> HttpConnectionHandler::serveSearchPage(const std::string &error) {
    http::response<http::string_body> response;
    response.version(11); // HTTP/1.1
    response.result(http::status::ok);
    response.set(http::field::server, "SearchEngine/1.0");
    response.set(http::field::content_type, "text/html; charset=utf-8");
    response.body() = ResponseTemplates::buildSearchPage(error);
    response.prepare_payload();
    return response;
}

http::response<http::string_body> HttpConnectionHandler::handleGetSearch(const std::string &target) {

    // Изымаем строку запроса после '?'
    size_t query_start = target.find('?');
    if (query_start == std::string::npos) {
        return serveSearchPage();
    }
    
    std::string query_string = target.substr(query_start + 1);
    auto params = ServerHttpUtils::parseQueryString(query_string);
    
    // Изымаем параметр 'q' (строка запроса)
    if (params.find("q") == params.end() || params["q"].empty()) {
        return serveSearchPage("Please enter a search query");
    }
    
    std::string query = params["q"];

    // Изымаем параметр 'limit' (макс. число результатов)    
    int limit = 10;
    if (params.find("limit") != params.end()) {
        try {
            limit = std::stoi(params["limit"]);
            limit = std::clamp(limit, 1, 100);
        } catch (...) {
            limit = 10;
        }
    }
    
    return performSearch(query, limit);
}

http::response<http::string_body> HttpConnectionHandler::handlePostSearch(const std::string &body) {
    auto params = ServerHttpUtils::parseQueryString(body);
    
    if (params.find("q") == params.end() || params["q"].empty()) {
        return serveSearchPage("Please enter a search query");
    }
    
    std::string query = params["q"];
    
    int limit = 10;
    if (params.find("limit") != params.end()) {
        try {
            limit = std::stoi(params["limit"]);
            limit = std::clamp(limit, 1, 100);
        } catch (...) {
            limit = 10;
        }
    }
    
    return performSearch(query, limit);
}

http::response<http::string_body> HttpConnectionHandler::performSearch(const std::string &query, int limit) {
    // Разделяем запрос на слова (разделитель - пробел)
    std::vector<std::string> words;
    std::istringstream iss(query);
    std::string word;
    
    while (iss >> word) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    
    if (words.empty()) {
        return serveSearchPage("Please enter at least one word");
    }

    std::vector<DatabaseManager::RelevanceSearchResult> results;   
    try {
        bool require_all_words = false; // Можно изменить на true, если нужно искать страницы, содержащие все слова
        results = db_manager_.searchPagesByRelevance(words, require_all_words, limit);
        
        std::cout << "Search for \"" << query << "\" returned " 
                    << results.size() << " results" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Database error: " << e.what() << std::endl;
        
        http::response<http::string_body> response;
        response.version(11);
        response.result(http::status::internal_server_error);
        response.set(http::field::server, "SearchEngine/1.0");
        response.set(http::field::content_type, "text/html; charset=utf-8");
        response.body() = ResponseTemplates::buildErrorPage(
            "Database query failed: " + std::string(e.what())
        );
        response.prepare_payload();
        return response;
    }
    
    // Формируем успешный ответ
    http::response<http::string_body> response;
    response.version(11);
    response.result(http::status::ok);
    response.set(http::field::server, "SearchEngine/1.0");
    response.set(http::field::content_type, "text/html; charset=utf-8");
    response.body() = ResponseTemplates::buildResultsPage(query, results, limit);
    response.prepare_payload();
    return response;
}

http::response<http::string_body> HttpConnectionHandler::serve404() {
    http::response<http::string_body> response;
    response.version(11);
    response.result(http::status::not_found);
    response.set(http::field::server, "SearchEngine/1.0");
    response.set(http::field::content_type, "text/html; charset=utf-8");
    response.body() = ResponseTemplates::build404Page();
    response.prepare_payload();
    return response;
}