#pragma once

#include <string>
#include <optional>
#include <memory>

#include "UrlParser.h"

struct CrawlParams
{
    DbInfo db_connection;
    UrlInfo url;
	int search_depth_max = 1;
	int	word_length_min = 3;
	int	word_length_max = 32;
	int thread_max = 0;

    int max_pages = 100;  // Ограничение на количество посещаемых страниц
    int timeout_seconds = 30;  // Request timeout
};

struct UrlInfo
{
    std::optional<Link> url_link_info; 
    // std::string address;
	int	search_depth = 0; // Deafault depth search

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

namespace Indexing {
    struct WordFrequency {
        std::string word;
        size_t frequency;
        
        WordFrequency(const std::string& w, size_t f) : word(w), frequency(f) {};
    };
}

struct DbInfo {
    std::string host;
    std::string port;
    std::string dbname;
    std::string user;
    std::string password;
};

struct CrawlResult {
    std::string url;
    std::string title;
    std::string content;
    std::vector<Indexing::WordFrequency> word_frequencies;
    
    CrawlResult(const std::string& u, const std::string& t, 
                const std::string& c, const std::vector<Indexing::WordFrequency>& wf)
        : url(u), title(t), content(c), word_frequencies(wf) {}
};



