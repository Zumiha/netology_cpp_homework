#include "DatabaseManager.h"
#include "DatabasePool.h"

DatabasePool::DatabasePool(const DatabaseManager::Config &config, size_t worker_count) : config_(config)
{   
    // Создание менеджеров баз данных для каждого рабочего потока
    connections_.reserve(worker_count);
    for (size_t i = 0; i < worker_count; ++i) {
        auto db = std::make_unique<DatabaseManager>(config_);
        if (!db->initialize()) {
            throw std::runtime_error("Failed to initialize database connection for worker " + std::to_string(i));
        }
        connections_.push_back(std::move(db));
    }

    if (connections_.empty()) {
        throw std::runtime_error("No database connections available.");
    }

    // Запуск рабочих потоков
    worker_threads_.reserve(worker_count);
    for (size_t i = 0; i < worker_count; ++i) {
        worker_threads_.emplace_back(&DatabasePool::workerLoop, this, i);
    }
    std::cout << "DatabasePool initialized with " << connections_.size() << " worker threads." << std::endl;
}

DatabasePool::~DatabasePool() {
    std::cout << "Destroying DatabasePool..." << std::endl;
    shutdown();    
}

void DatabasePool::queueResult(const std::string &url, const std::string &title, const std::string &content, const std::vector<Indexing::WordFrequency> &frequencies) {
    if (shutdown_requested_) {
        throw std::runtime_error("Cannot queue results after shutdown has been requested.");
    }
    std::cout << "\nAttemnt to push data to results queue..\n" << std::endl;
    pending_results_.push(CrawlResult(url, title, content, frequencies));
}

void DatabasePool::queueResult(const CrawlResult &_res)
{
    if (shutdown_requested_) {
        throw std::runtime_error("Cannot queue results after shutdown has been requested.");
    }
    std::cout << "\nAttemnt to push data to results queue..\n" << std::endl;
    pending_results_.push(_res);
}

void DatabasePool::shutdown() {
    if (shutdown_requested_.exchange(true)) {
        return; // Уже запрошено завершение
    }
    std::cout << "Shutting down DatabasePool..." << std::endl;

    // Ожидание завершения рабочих потоков
    for (auto& thread : worker_threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    std::cout << "DatabasePool shutdown complete." << std::endl;
}

size_t DatabasePool::getPendingCount() const {
    return pending_results_.size();
}

size_t DatabasePool::getProcessedCount() const {
    return processed_count_.load();
}

// private methods

void DatabasePool::workerLoop(size_t worker_id) {
    DatabaseManager& db = *connections_[worker_id];
    std::vector<CrawlResult> batch;
    batch.reserve(10); // Пакетная обработка по 10 задач
    
    while (!shutdown_requested_.load() || !pending_results_.empty()) { // Продолжаем, пока не запрошено завершение и есть задачи
        batch.clear();        
        CrawlResult result("", "", "", {});

        // Собираем пакет задач
        while (batch.size() < 10 && pending_results_.pop(result)) {
            batch.push_back(std::move(result));
        }

        if (!batch.empty()) {
            if (processBatch(db, batch)) {
                processed_count_ += batch.size();
                std::cout << "Worker " << worker_id << " processed batch of " << batch.size() << " results. Total processed: " << processed_count_.load() << std::endl;
            } else {
                std::cerr << "Worker " << worker_id << " failed to process batch." << std::endl;
            }   
        } else if (!shutdown_requested_.load()) {
            // Нет задач, небольшой сон чтобы не крутить цикл впустую
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

bool DatabasePool::processBatch(DatabaseManager &db, std::vector<CrawlResult> &batch) {
    try {
        bool all_success = true;
        int successful_inserts = 0;
        std::cout << "\nProcessing batch of size: " << batch.size() << std::endl;
        for (const auto& result : batch) {
            // Вставка страницы
            std::cout << "\nInserting page: " << result.url;
            std::cout << "\nTitle: " << result.title;
            std::cout << "\nContent: present" << std::endl;
            auto page_id = db.insertPage(result.url, result.title, result.content);
            std::cout << "\nPage ID: " << page_id.value() << std::endl;
            
            if (!page_id.has_value()) {
                std::cerr << "Failed to insert page for URL: " << result.url << std::endl;
                all_success = false;
                continue;
            }

            if (result.word_frequencies.empty()) {
                std::cerr << "No word frequencies to store for URL: " << result.url << std::endl;
                continue;
            }

            if (!db.storeWordFrequencies(*page_id, result.word_frequencies)) {
                std::cerr << "Failed to store word frequencies for URL: " << result.url << std::endl;
                all_success = false;
            }
            std::cout << "Successfull inserts: " << ++successful_inserts << std::endl;
        }        
        return all_success;
    } catch (const std::exception &e) {
        std::cerr << "Error processing batch: " << e.what() << std::endl;
        return false;
    }
}