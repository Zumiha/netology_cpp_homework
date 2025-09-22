#pragma once

#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <optional>
#include <chrono>

#include "struct.h"
#include "Indexer.h"

class DatabaseManager {
public:
    struct Config {
        std::string host = "localhost";
        std::string port = "5432";
        std::string dbname = "spider_index";
        std::string user = "admin";
        std::string password = "admin";
        int max_connections = 10;
        std::chrono::seconds connection_timeout{30};
    };

    struct RelevanceSearchResult {
        int page_id;
        std::string url;
        std::string title;
        int total_relevance;
        std::vector<std::pair<std::string, int>> word_frequencies; // word -> frequency pair
    };

    explicit DatabaseManager(const DbInfo& db_info);
    explicit DatabaseManager(const Config& config);
    ~DatabaseManager();

    // Инициализация и создание таблиц
    bool initialize();
    bool createTables();

    // Соединение
    bool testConnection();
    void closeConnection();
    
    // Операции с страницами
    std::optional<int> insertPage(const std::string& url, const std::string& title, const std::string& content);
    bool pageExists(const std::string& url);
    std::optional<int> getPageId(const std::string& url);
    
    // Операции с словами
    bool storeWordFrequencies(int page_id, const std::vector<Indexing::WordFrequency>& frequencies);
    
    // Поисковые запросы
    std::vector<RelevanceSearchResult> searchPagesByRelevance(const std::vector<std::string>& words, bool require_all_words, int limit = 10);
    // std::vector<Indexing::WordFrequency> getPageWordFrequencies(int page_id);
    
    // Статистика
    size_t getTotalPages();
    size_t getTotalWords();
    size_t getUniqueWords();


private:
    Config config_;
    std::unique_ptr<pqxx::connection> conn_;
    mutable std::mutex conn_mutex_;    
    std::string buildConnectionString() const;    
    // Запросы создания таблиц
    static const std::string CREATE_PAGES_TABLE;
    static const std::string CREATE_WORDS_TABLE;
    // static const std::string CREATE_PAGE_WORDS_TABLE;
};

// Многопоточный пул соединений (не реализован)
// class DatabasePool {
// public:
//     explicit DatabasePool(const DatabaseManager::Config& config, size_t pool_size = 5);
//     ~DatabasePool();
    
//     std::shared_ptr<DatabaseManager> getConnection();
//     void returnConnection(std::shared_ptr<DatabaseManager> db);
    
// private:
//     DatabaseManager::Config config_;
//     std::queue<std::shared_ptr<DatabaseManager>> available_connections_;
//     std::mutex pool_mutex_;
//     std::condition_variable pool_cv_;
//     size_t pool_size_;
//     size_t active_connections_;
// };