#pragma once

#include <memory>
#include <unordered_set>

#include <regex>
#include <algorithm>
#include <cctype>

#include "IniParser.h"
#include "ThreadPool.h"
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
    std::string address;
	int	search_depth = 1;

    UrlInfo() = default;
    UrlInfo(const std::string& addr, int depth) : address(addr), search_depth(depth) {}
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


class webCrawler {
public:
    webCrawler(int argc, char* argv[]);
    ~webCrawler();
    


    void startCrawling();
    void stopCrawling();
    void printSettings();
    
    // Statistics
    int getVisitedCount() const { return visited_urls.size(); }
    int getPendingCount() const { return pending_count.load(); }
    int getActiveWorkers() const { return active_workers.load(); }
    
protected:
    void setSearchSettings();
    
private:
    void crawlUrl(UrlInfo url_data);

    std::string downloadPage(const std::string& url);
    void processPage(const std::string& url, const std::string& content, int current_depth);
    void extractLinks(const std::string& content, const std::string& base_url, int current_depth);
    void indexWords(const std::string& content, const std::string& url);
    std::string normalizeUrl(const std::string& url, const std::string& base_url);
    bool isValidUrl(const std::string& url);
    
    // Configuration
    std::unique_ptr<IniParser> parser;
    std::string ini_file_name = "crawlerdata.ini";
    CrawlParams search_settings;

    // Threading
    std::unique_ptr<ThreadPool> work_pool;

    // URL management
    SafeQueue<UrlInfo> pending_urls;
    std::unordered_set<std::string> visited_urls;
    std::mutex visited_mutex;

    // Control variables
    std::atomic<int> active_workers{0};
    std::atomic<int> pending_count{0};
    std::atomic<bool> should_stop{false};
    std::atomic<bool> is_running{false};
    
    // Statistics
    std::atomic<int> total_pages_crawled{0};
    std::atomic<int> total_words_indexed{0};
    
    // // Synchronization
    // std::condition_variable completion_cv;
    // std::mutex completion_mutex;
};