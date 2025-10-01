#include "SearchEngine.h"

SearchServer::SearchServer(short port, DatabaseManager& db_manager, ThreadMode mode) 
        : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)), 
        db_manager_(db_manager), 
        mode_(mode), 
        thread_pool_(nullptr)
{
    if (mode_ == ThreadMode::THREAD_POOL) {
        thread_pool_ = std::make_unique<ThreadPool>();
        std::cout << 
            "Using ThreadPool with " << 
            thread_pool_->getCPUcount() << 
            " worker threads" << std::endl;
    } else {
        std::cout << "Using detached thread per connection" << std::endl;
    }
}

void SearchServer::run() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Search Engine Server Starting" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Port: " << acceptor_.local_endpoint().port() << std::endl;
    std::cout << "URL: http://localhost:" << acceptor_.local_endpoint().port() << std::endl;
    std::cout << "Press Ctrl+C to stop" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    while (running_) {
        try {
            tcp::socket socket(io_context_);
            acceptor_.accept(socket);
            
            std::cout << "New connection from " << socket.remote_endpoint() << std::endl;
            
            if (mode_ == ThreadMode::THREAD_POOL) {
                thread_pool_->submit([socket = std::move(socket), this]() mutable {
                    HttpConnectionHandler handler(std::move(socket), db_manager_);
                    handler.handle();
                });
            } else {
                std::thread([socket = std::move(socket), this]() mutable {
                    HttpConnectionHandler handler(std::move(socket), db_manager_);
                    handler.handle();
                }).detach();
            }
            
        } catch (const std::exception& e) {
            if (running_) {
                std::cerr << "Accept error: " << e.what() << std::endl;
            }
        }
    }
    
    std::cout << "\nServer stopped." << std::endl;
}

void SearchServer::stop() {
    running_ = false;
    acceptor_.close();
}