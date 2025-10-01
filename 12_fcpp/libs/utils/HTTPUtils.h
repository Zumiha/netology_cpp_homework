#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <optional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <openssl/ssl.h>

#include <algorithm>
#include <cctype>

#include "UrlParser.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = net::ip::tcp;

class HTTPUtils {
public:
    struct Config {
        std::chrono::seconds timeout{30};
        std::string userAgent{"HTTPUtils/1.0"};
        bool verifySSL{false};
        bool textOnly{true};
        bool followRedirects{true};      // Можно/нельзя ходить по редиректам
        int maxRedirects{5};             // Сколько редиректов максимально
        bool relaxedTextDetection{true}; // Нестрого/строго определять текст
    };

    static std::optional<std::string> fetchPage(const Link& url, const Config& config);
    
private:
    static bool isTextContent(const std::string& content);
    static bool isRedirectResponse(int statusCode);
    static std::optional<std::string> handleHttps(net::io_context& ioc, Link& currentUrl, int& redirectCount, const Config& config);
    static std::optional<std::string> handleHttp(net::io_context& ioc, Link& currentUrl, int& redirectCount, const Config& config);

    template<typename ResponseType>
    static std::optional<Link> handleRedirect(const ResponseType& response, const Link& currentUrl, int redirectCount, const Config& config) {
        if (!config.followRedirects || !isRedirectResponse(response.result_int())) {
        return std::nullopt; // Не ридерект или редиректы отключены
    }
    
    auto location_it = response.find(http::field::location);
    if (location_it != response.end()) {
        std::string redirectUrl = std::string(location_it->value());
        std::cout << "Redirect " << (redirectCount + 1) << " from " << currentUrl.link << " to " << redirectUrl << std::endl;
        
        auto parsedRedirect = URLParser::parse(redirectUrl);
        if (parsedRedirect.has_value()) {
            return parsedRedirect.value();
        }
    }
    
    return std::nullopt; // Не получилось обработать редирект
    };    
};