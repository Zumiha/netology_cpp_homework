#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <csignal>
#include <atomic>

#include "DatabaseManager.h"
#include "struct.h"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using tcp = asio::ip::tcp;

class ServerHttpUtils {
public:

    // Парсим строку запроса вида "q=hello+world&limit=10" в map ключ-значение
    static std::unordered_map<std::string, std::string> parseQueryString(const std::string& query_str);

    // Обработанная ссылка: "hello+world" -> "hello world", "%20" -> " "
    static std::string urlDecode(const std::string& encoded);
    
    // HTML escape для безопасного вывода (предотвращение XSS)
    static std::string htmlEscape(const std::string& text);
};

class ResponseTemplates {
public:
    static std::string buildSearchPage(const std::string& error_msg = "");    
    static std::string buildResultsPage(
        const std::string& query, 
        const std::vector<DatabaseManager::RelevanceSearchResult>& results, 
        int limit
    );    
    static std::string build404Page();    
    static std::string buildErrorPage(const std::string& error);
};

class HttpConnectionHandler {
public:
    HttpConnectionHandler(tcp::socket socket, DatabaseManager& db_manager)
        : socket_(std::move(socket)), db_manager_(db_manager) {};
    
    // Основной обработчик - обрабатывает один полный цикл HTTP-запроса/ответа

    void handle();

private:
    tcp::socket socket_;
    DatabaseManager& db_manager_;
    
    http::response<http::string_body> processRequest(const http::request<http::string_body>& request);    
    http::response<http::string_body> serveSearchPage(const std::string& error = "");    
    http::response<http::string_body> handleGetSearch(const std::string& target);    
    http::response<http::string_body> handlePostSearch(const std::string& body);
    
    http::response<http::string_body> performSearch(const std::string& query, int limit);    
    http::response<http::string_body> serve404();
};