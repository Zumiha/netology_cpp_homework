#include "Crawler.h"

int main(int argc, char* argv[]) {   
    try {
        webCrawler spider(argc, argv);
        // spider.printSettings();  
        std::cout << "Creating crawler";
        spider.startCrawling();
        std::cout << "\n...Crawler destroyed....\n";
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}