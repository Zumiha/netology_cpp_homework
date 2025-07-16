#include "HTTPUtils.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <openssl/ssl.h>

#include <iostream>
#include <algorithm>
#include <cctype>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = net::ip::tcp;

bool HTTPUtils::isTextContent(const std::string& content) {
    if (content.empty()) return false;
    
    // Check for null bytes in first 1024 characters (or full content if shorter)
    size_t checkLength = std::min(content.length(), size_t(1024));
    for (size_t i = 0; i < checkLength; ++i) {
        if (content[i] == '\0') {
            return false;
        }
    }
    
    // Count printable characters
    size_t printableCount = 0;
    for (size_t i = 0; i < checkLength; ++i) {
        if (std::isprint(static_cast<unsigned char>(content[i])) || 
            std::isspace(static_cast<unsigned char>(content[i]))) {
            printableCount++;
        }
    }
    
    // Consider it text if at least 95% of characters are printable
    return (printableCount * 100 / checkLength) >= 95;
}

std::optional<std::string> HTTPUtils::fetchPage(const Link& url, const Config& config) {
    net::io_context ioc;
    
    try {
        if (url.protocol == ProtocolType::HTTPS) {
            // HTTPS implementation
            ssl::context ctx(ssl::context::tlsv12_client);
            // ctx.set_default_verify_paths();
            
            if (config.verifySSL) {
                ctx.set_default_verify_paths();
                ctx.set_verify_mode(ssl::verify_peer);
            } else {
                ctx.set_verify_mode(ssl::verify_none);
            }
            
            beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);
            
            // Set SNI hostname
            if (!SSL_set_tlsext_host_name(stream.native_handle(), url.hostName.c_str())) {
                beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
                std::cerr << "Failed to set SNI hostname: " << ec.message() << std::endl;
                return std::nullopt;
            }
            
            // Set timeout
            beast::get_lowest_layer(stream).expires_after(config.timeout);
            
            // Resolve and connect
            tcp::resolver resolver(ioc);
            auto const results = resolver.resolve(url.hostName, "443");
            beast::get_lowest_layer(stream).connect(results);
            
            // Perform SSL handshake
// stream.handshake(ssl::stream_base::client);
            beast::error_code handshake_ec;
            stream.handshake(ssl::stream_base::client, handshake_ec);
            if (handshake_ec) {
                std::cerr << "SSL handshake failed: " << handshake_ec.message() << std::endl;
                return std::nullopt;
            }

            // Set up HTTP request
            http::request<http::empty_body> req{http::verb::get, url.query, 11};
            req.set(http::field::host, url.hostName);
            req.set(http::field::user_agent, config.userAgent);
            req.set(http::field::connection, "close");
            
            // Send request
// http::write(stream, req);
            beast::error_code write_ec;
            http::write(stream, req, write_ec);
            if (write_ec) {
                std::cerr << "Failed to write request: " << write_ec.message() << std::endl;
                return std::nullopt;
            }
            
            // Read response
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
// http::read(stream, buffer, res);
            beast::error_code read_ec;
            http::read(stream, buffer, res, read_ec);
            if (read_ec) {
                std::cerr << "Failed to read response: " << read_ec.message() << std::endl;
                return std::nullopt;
            }
            
            // Convert response body to string
            std::string content = beast::buffers_to_string(res.body().data());
            
            // Check if content is text (if required)
            if (config.textOnly && !isTextContent(content)) {
                std::cerr << "Content is not text, skipping..." << std::endl;
                return std::nullopt;
            }
            
            // Clean shutdown
            beast::error_code ec;
            stream.shutdown(ec);
            if (ec == net::error::eof) {
                ec = {};
            }
            
            return content;
            
        } else {
            // HTTP implementation
            tcp::resolver resolver(ioc);
            beast::tcp_stream stream(ioc);
            
            // Set timeout
            stream.expires_after(config.timeout);
            
            // Resolve and connect
            auto const results = resolver.resolve(url.hostName, "80");
            stream.connect(results);
            
            // Set up HTTP request
            http::request<http::empty_body> req{http::verb::get, url.query, 11};
            req.set(http::field::host, url.hostName);
            req.set(http::field::user_agent, config.userAgent);
            req.set(http::field::connection, "close");
            
            // Send request
            http::write(stream, req);
            
            // Read response
            beast::flat_buffer buffer;
            http::response<http::dynamic_body> res;
            http::read(stream, buffer, res);
            
            // Convert response body to string
            std::string content = beast::buffers_to_string(res.body().data());
            
            // Check if content is text (if required)
            if (config.textOnly && !isTextContent(content)) {
                std::cerr << "Content is not text, skipping..." << std::endl;
                return std::nullopt;
            }
            
            // Clean shutdown
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);
            if (ec && ec != beast::errc::not_connected) {
                // Log but don't throw on shutdown errors
                std::cerr << "Shutdown error: " << ec.message() << std::endl;
            }
            
            return content;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "HTTP request failed for " << url.hostName << ": " << e.what() << std::endl;
        return std::nullopt;
    }
}