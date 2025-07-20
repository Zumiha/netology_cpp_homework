#pragma once

#include <unordered_set>
#include <optional>

#include <regex>
#include <algorithm>
#include <cctype>

#include "struct.h"
#include "IniParser.h"
#include "ThreadPool.h"
#include "UrlParser.h"
#include "HTTPUtils.h"
#include "HtmlParser.h"
#include "Indexer.h"

class webCrawler {
public:
    webCrawler(int argc, char* argv[]);
    ~webCrawler();
    
    CrawlParams params_getter() {return this->search_settings;};

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
    
    void indexWords(const std::string& content, const std::string& url);
    
    // Configuration
    CrawlParams search_settings;
    std::unique_ptr<IniParser> parser;
    std::string ini_file_name = "crawlerdata.ini";

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
    std::mutex count_mutex;

    // Indexer
    // std::unique_ptr<TextIndexer> Indexer;

    //Tests
    SafeQueue<std::string> page_text;
};