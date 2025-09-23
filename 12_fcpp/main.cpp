#include "Crawler.h"

int main(int argc, char* argv[]) {   
    try {
        webCrawler spider(argc, argv);
        // spider.printSettings();  
        // spider.startCrawling();
        DatabaseManager db_manager(spider.params_getter().db_connection);
        if (db_manager.testConnection()) {
            std::cout << "Database connection successful!" << std::endl;
        } else {
            std::cerr << "Database connection failed!" << std::endl;
            return 1;
        }
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}