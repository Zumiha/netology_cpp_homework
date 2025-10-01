#include "SearchEngine.h"

std::unique_ptr<SearchServer> g_server;

void signalHandler(int signum) {
    std::cout << "\n\nReceived signal " << signum << ", shutting down gracefully..." << std::endl;
    if (g_server) {
        g_server->stop();
    }
}

int main(int argc, char* argv[]) {
    try {
        SearchServer::Config config_;
        IniParser parser("search_engine.ini");
        
        config_.host = parser.getValue<std::string>("server.host");
        config_.port = parser.getValue<int>("server.port");
        config_.max_search_words = parser.getValue<int>("search.max_words");
        config_.max_results = parser.getValue<int>("search.max_results");
        
        config_.db_config.host = parser.getValue<std::string>("db.host");
        config_.db_config.port = parser.getValue<std::string>("db.port");
        config_.db_config.dbname = parser.getValue<std::string>("db.dbname");
        config_.db_config.user = parser.getValue<std::string>("db.user");
        config_.db_config.password = parser.getValue<std::string>("db.password");
      
        std::cout << "Connecting to PostgreSQL database..." << std::endl;
        std::cout << "Host: " << config_.host << ":" << config_.port << std::endl;
        std::cout << "Database: " << config_.db_config.dbname << std::endl;
        
        DatabaseManager db_manager(config_.db_config);
        
        if (!db_manager.initialize()) {
            std::cerr << "Failed to initialize database connection!" << std::endl;
            std::cerr << "Make sure PostgreSQL is running and credentials are correct." << std::endl;
            return 1;
        }
        
        if (!db_manager.testConnection()) {
            std::cerr << "Database connection test failed!" << std::endl;
            return 1;
        }
        
        std::cout << "Database connected successfully!\n" << std::endl;
        
        // Назначаем обработчики сигналов для корректного завершения (Ctrl+C)
        std::signal(SIGINT, signalHandler);
        std::signal(SIGTERM, signalHandler);
        
        // Создаем и запускаем сервер
        g_server = std::make_unique<SearchServer>(
            config_.port, 
            db_manager, 
            SearchServer::ThreadMode::THREAD_POOL
        );
        
        g_server->run();
        
        db_manager.closeConnection();
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}