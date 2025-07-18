#pragma once

#include <string>
#include <optional>

#include "UrlParser.h"

struct DbInfo {
    std::string host;
    std::string port;
    std::string dbname;
    std::string user;
    std::string password;
};

struct UrlInfo
{
    std::optional<Link> url_link_info; 
    // std::string address;
	int	search_depth = 1; // Deafault depth search

    UrlInfo() = default;
    UrlInfo(const std::string& addr, int depth) {
        url_link_info = URLParser::parse(addr); // Если передается строка в конструктор, то сразу парсим
        search_depth = depth;        
    }
    UrlInfo(const std::optional<Link>& link, int depth) {
        url_link_info = link;
        search_depth = depth;        
    }
    UrlInfo(const Link& link, int depth) { // Конструктор с просто Link структурой
        url_link_info = link;
        search_depth = depth;
    }
};

struct CrawlParams
{
    DbInfo db_connection;
    UrlInfo url;
	int	word_length_min = 3;
	int	word_length_max = 32;
	int thread_max = 0;

    int max_pages = 1000;  // Ограничение на количество посещаемых страниц
    int timeout_seconds = 30;  // Request timeout
};


