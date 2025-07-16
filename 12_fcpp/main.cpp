#include "Crawler.h"

int main(int argc, char* argv[]) {   
    try {
        webCrawler spider(argc, argv);
        spider.printSettings();  
        spider.startCrawling();

    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}