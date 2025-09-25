#include "DatabaseManager.h"
#include <iostream>
#include <sstream>
#include <algorithm>

#include <boost/algorithm/string/join.hpp>

DatabaseManager::DatabaseManager(const DbInfo& db_info) {
    config_.host = db_info.host;
    config_.port = db_info.port;
    config_.dbname = db_info.dbname;
    config_.user = db_info.user;
    config_.password = db_info.password;
}

DatabaseManager::DatabaseManager(const Config& config) : config_(config) {}

DatabaseManager::~DatabaseManager() {
    closeConnection();
}

bool DatabaseManager::initialize() {
    try {

        if (conn_ && conn_->is_open()) {
            return true; // Уже подключено
        }
        
        std::string conn_str = buildConnectionString();
        conn_ = std::make_unique<pqxx::connection>(conn_str);
        
        if (!conn_->is_open()) {
            std::cerr << "Failed to open database connection." << std::endl;
            return false;
        }
        return createTables();        
    } catch (const std::exception& e) {
        std::cerr << "Database connection error: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::createTables() {
    try {
        pqxx::work txn(*conn_);
        txn.exec(CREATE_PAGES_TABLE);
        txn.exec(CREATE_WORDS_TABLE);

        txn.commit();

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error creating tables: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::testConnection() {
    try {
        std::lock_guard<std::mutex> lock(conn_mutex_);
        if (conn_ && conn_->is_open()) {
            pqxx::work txn(*conn_);
            txn.exec("SELECT 1");
            return true;
        }
        return initialize();
    } catch (const std::exception& e) {
        std::cerr << "Connection test error: " << e.what() << std::endl;
        return false;
    }
}

void DatabaseManager::closeConnection() {
    std::lock_guard<std::mutex> lock(conn_mutex_);
    if (conn_ && conn_->is_open()) {
        conn_->close();
        std::cout << "Database connection closed." << std::endl;
    }
}

// Сохранение страницы с обновлением при конфликте URL, возвращает id страницы
std::optional<int> DatabaseManager::insertPage(const std::string& url, const std::string& title, const std::string& content) {
    try {
        std::lock_guard<std::mutex> lock(conn_mutex_);
        if (!conn_ || !conn_->is_open()) {
            if (!initialize()) {
                return std::nullopt;
            }
        }
        pqxx::work txn(*conn_);        
        std::string content_hash = std::to_string(std::hash<std::string>{}(content));
        std::string query = R"(
            INSERT INTO pages (url, title, content_hash)
            VALUES ($1, $2, $3)
            ON CONFLICT (url) DO UPDATE SET
                title = EXCLUDED.title,
                content_hash = EXCLUDED.content_hash
            RETURNING id
            )";
        
        pqxx::result insert_result = txn.exec_params(query, url, title, content_hash);
        txn.commit();
        
        if (!insert_result.empty()) {
            return insert_result[0][0].as<int>();
        }
        return std::nullopt;

    } catch (const std::exception& e) {
        std::cerr << "Error inserting/updating page: " << e.what() << std::endl;
        return std::nullopt;
    }

}

// Проверка существования страницы по URL
bool DatabaseManager::pageExists(const std::string& url) {
    try {
        std::lock_guard<std::mutex> lock(conn_mutex_);
        if (!conn_ || !conn_->is_open()) return false;
        
        pqxx::nontransaction nontxn(*conn_);
        pqxx::result r = nontxn.exec_params(
            "SELECT 1 FROM pages WHERE url = $1 LIMIT 1", url);
        return !r.empty();
        
    } catch (const std::exception& e) {
        std::cerr << "Error checking page existence: " << e.what() << std::endl;
        return false;
    }
}

// Получение ID страницы по URL
std::optional<int> DatabaseManager::getPageId(const std::string& url) {
    try {
        std::lock_guard<std::mutex> lock(conn_mutex_);
        if (!conn_ || !conn_->is_open()) return std::nullopt;
        
        pqxx::nontransaction nontxn(*conn_);
        pqxx::result r = nontxn.exec_params(
            "SELECT id FROM pages WHERE url = $1 LIMIT 1", url);
        
        if (!r.empty()) {
            return r[0][0].as<int>();
        }
        return std::nullopt;
        
    } catch (const std::exception& e) {
        std::cerr << "Error getting page ID: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool DatabaseManager::storeWordFrequencies(int page_id, const std::vector<Indexing::WordFrequency>& frequencies) {
    if (!conn_ || !conn_->is_open() || frequencies.empty()) {
        return false;
    }

    try {
        std::lock_guard<std::mutex> lock(conn_mutex_);
        pqxx::work txn(*conn_);

        // Получаем id страницы
        auto result = txn.exec_params("SELECT id FROM pages WHERE id = $1", page_id);
        if (result.empty()) {
            std::cerr << "Page ID " << page_id << " does not exist." << std::endl;
            return false;
        }

        int page_id = result[0][0].as<int>();

        // Удалить существующие записи для этой страницы
        txn.exec_params("DELETE FROM word_frequencies WHERE page_id = $1", page_id);

        // Вставить новые слова и частоты
        std::ostringstream insert_query;
        insert_query << "INSERT INTO word_frequencies (page_id, word, frequency) VALUES ";

        bool first = true;
        for (const auto& wf : frequencies) {
            if(!first) insert_query << ", ";
            insert_query << "(" << page_id << ", " << txn.quote(wf.word) << ", " << wf.frequency << ")";
            first = false;
        }
        txn.exec(insert_query.str());
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error storing word frequencies: " << e.what() << std::endl;
        return false;
    }
}

std::vector<DatabaseManager::RelevanceSearchResult> DatabaseManager::searchPagesByRelevance(const std::vector<std::string> &words, bool require_all_words, int limit)
{
    std::vector<RelevanceSearchResult> results;
    if (words.empty() || !conn_ || !conn_->is_open()) return results;

    try {
        std::lock_guard<std::mutex> lock(conn_mutex_);
        pqxx::nontransaction nontxn(*conn_);

        std::ostringstream query;
        
        // Создание таблицы с найденными словами
        query << R"(
            WITH word_matches AS (
                SELECT p.id AS page_id, p.url, p.title, wf.word, wf.frequency
                FROM word_frequencies wf
                JOIN pages p ON wf.page_id = p.id
                WHERE LOWER(wf.word) IN (
        )";
        
        // Добавление слов в запрос (по размеру вектора words)
        for (size_t i = 0; i < words.size(); ++i) {
            if (i > 0) query << ", ";
            query << "$" << (i + 1);
        }

        // Продолжение запроса. Создание агрегированной таблицы и пар слово-частота
        query << R"(
                )
            ),
            page_relevance AS (
                SELECT page_id, url, title, SUM(frequency) AS total_relevance, COUNT(DISTINCT word) AS unique_words_found,
                ARRAY_AGG((word || ':' || frequency::text ORDER BY frequency DESC)) AS word_freq_pairs
                FROM word_matches 
                GROUP BY page_id, url, title
        )"; 

        // Запрос с условием на количество уникальных слов
        if (require_all_words) {
            query << R"(
            SELECT page_id, url, title, total_relevance, word_freq_pairs
            FROM page_relevance
            WHERE unique_words_found = $)" << (words.size() + 1) << R"(
            ORDER BY total_relevance DESC
            LIMIT $)" << (words.size() + 2);
        } else {
            query << R"(
            SELECT page_id, url, title, total_relevance, word_freq_pairs
            FROM page_relevance
            ORDER BY total_relevance DESC
            LIMIT $)" << (words.size() + 1) << R"(
            )";
        }

        // Подготовка параметров запроса
        pqxx::params params;
        for (const auto &word : words) { // Добавляем слова в нижнем регистре
            params.append(boost::locale::to_lower(word));
        }
        if (require_all_words) { 
            params.append(static_cast<int>(words.size()));
        }
        params.append(static_cast<int>(limit)); // Лимит результатов
        
        auto result = nontxn.exec_params(query.str(), params); 

        // Обработка результатов. Заполнение массива структур RelevanceSearchResult
        for (const auto &row : result) {
            RelevanceSearchResult res;

            // Заполнение структуры основными полями
            res.page_id = row["page_id"].as<int>();
            res.url = row["url"].as<std::string>();
            res.title = row["title"].as<std::string>();
            res.total_relevance = row["total_relevance"].as<int>();

            // Разбор массива word_freq_pairs
            std::string word_freq_array = row["word_freq_pairs"].as<std::string>();
            // Удаление фигурных скобок
            if(word_freq_array.front() == '{') word_freq_array.erase(0, 1);
            if(word_freq_array.back() == '}') word_freq_array.pop_back();

            // Разделение по запятым
            std::istringstream ss(word_freq_array);
            std::string pair;

            while (std::getline(ss, pair, ',')) {
                // Удаление кавычек, если есть
                if(word_freq_array.front() == '"') pair.erase(0, 1);
                if(word_freq_array.back() == '"') pair.pop_back();

                // Разделение слова и частоты по двоеточию
                size_t delim_pos = pair.find(':');
                if (delim_pos != std::string::npos) {
                    std::string word = pair.substr(0, delim_pos);
                    int frequency = std::stoi(pair.substr(delim_pos + 1));
                    // Добавление в вектор пар слово-частота
                    res.word_frequencies.emplace_back(word, frequency);
                }
            }
            results.push_back(std::move(res));
        }
    } catch (const std::exception &e) {
        std::cerr << "Relevance search error: " << e.what() << std::endl;
    }
    return results;
}

// Private methods

std::string DatabaseManager::buildConnectionString() const {
    std::ostringstream oss;
    oss << "host=" << config_.host
        << " port=" << config_.port
        << " dbname=" << config_.dbname
        << " user=" << config_.user
        << " password=" << config_.password
        << " connect_timeout=" << config_.connection_timeout.count();
    return oss.str();
}

// Запросы создания таблиц
const std::string DatabaseManager::CREATE_PAGES_TABLE = R"(
    CREATE TABLE IF NOT EXISTS pages (
        id SERIAL PRIMARY KEY,
        url TEXT UNIQUE NOT NULL,
        title TEXT,
        content_hash TEXT
    )
)";

const std::string DatabaseManager::CREATE_WORDS_TABLE = R"(
    CREATE TABLE IF NOT EXISTS word_frequencies (
        id SERIAL PRIMARY KEY,
        page_id INTEGER REFERENCES pages(id) ON DELETE CASCADE,
        word VARCHAR(32) NOT NULL,
        frequency INTEGER NOT NULL DEFAULT 1,
        UNIQUE(page_id, word)
    )
)";