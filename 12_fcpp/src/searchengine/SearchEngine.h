#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <csignal>
#include <atomic>

#include "struct.h"
#include "IniParser.h"
#include "ThreadPool.h"
#include "DatabaseManager.h"
#include "ServerHttpUtils.h"

class SearchServer {
public:
    enum class ThreadMode {
        DETACHED,    
        THREAD_POOL  // используем ThreadPool
    };

    struct Config {
        std::string host = "localhost";
        int port = 8080;
        int max_search_words = 4;
        int max_results = 10;
        DatabaseManager::Config db_config;
    };
    
    SearchServer(
        short port, 
        DatabaseManager& db_manager, 
        ThreadMode mode = ThreadMode::THREAD_POOL
    );    

    void run();    
    void stop();

private:
    asio::io_context io_context_;
    tcp::acceptor acceptor_;
    DatabaseManager& db_manager_;
    ThreadMode mode_;
    std::unique_ptr<ThreadPool> thread_pool_;
    std::atomic<bool> running_{true};
};