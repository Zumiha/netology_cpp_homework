#pragma once

#include "DatabaseManager.h"
#include "SafeQueue.h"
#include <thread>
#include <atomic>
#include <vector>
#include <memory>

class DatabasePool {
public:
    explicit DatabasePool(const DatabaseManager::Config& config, size_t worker_count = 2);
    ~DatabasePool();
    
    // Добавление задачи потоками, без блокировок
    void queueResult(
        const std::string& url, 
        const std::string& title,
        const std::string& content,
        const std::vector<Indexing::WordFrequency>& frequencies
    );

    // Остановска для безопасного завершения потоков
    void shutdown();
    // Получение статистики
    size_t getPendingCount() const;
    size_t getProcessedCount() const;

private:
    DatabaseManager::Config config_;

    SafeQueue<CrawlResult> pending_results_;
    std::vector<std::unique_ptr<DatabaseManager>> connections_;

    std::vector<std::thread> worker_threads_;
    std::atomic<size_t> processed_count_{0};
    
    std::atomic<bool> shutdown_requested_{false};
    
    void workerLoop(size_t worker_id);
    bool processBatch(DatabaseManager& db, std::vector<CrawlResult>& batch);

}   