#include "Crawler.h"

// webCrawler::webCrawler(std::string& _str)
// {
//     if (_str != "") {this->parser = new IniParser(_str);}
//     else {this->parser = new IniParser(ini_file_name);}
// }

// webCrawler::~webCrawler()
// {
//     if (this->parser != nullptr) {
//         delete this->parser;
//         this->parser = nullptr;
//     }
// }

webCrawler::webCrawler(int argc, char* argv[])
{
    if (argc < 2) {this->parser = std::make_unique<IniParser>(ini_file_name); std::cout << "created object with default file\n";}
    else {this->parser = std::make_unique<IniParser>(argv[argc-1]); std::cout << "created object with declared file\n";}

    this->setSearchSettings();
}

webCrawler::~webCrawler()
{
}

void webCrawler::setSearchSettings()
{
    this->search_settings.url = this->parser->getValue<std::string>("url.urltest");

    this->search_settings.db_connection.host = this->parser->getValue<std::string>("db.host");
    this->search_settings.db_connection.port = this->parser->getValue<std::string>("db.port");
    this->search_settings.db_connection.dbname = this->parser->getValue<std::string>("db.dbname");
    this->search_settings.db_connection.user = this->parser->getValue<std::string>("db.user");
    this->search_settings.db_connection.password = this->parser->getValue<std::string>("db.password");
    
    this->search_settings.search_depth = this->parser->getValue<int>("indexing.search_depth");
    this->search_settings.word_length_min = this->parser->getValue<int>("indexing.word_length_min");
    this->search_settings.word_length_max = this->parser->getValue<int>("indexing.word_length_max");

    this->search_settings.thread_max = this->parser->getValue<int>("threading.thread_max");
}

void webCrawler::printSettings()
{
    std::cout << "\n";
    std::cout << this->search_settings.url << "\n";

    std::cout << this->search_settings.db_connection.host << "\n";
    std::cout << this->search_settings.db_connection.port << "\n";
    std::cout << this->search_settings.db_connection.dbname << "\n";
    std::cout << this->search_settings.db_connection.user << "\n";
    std::cout << this->search_settings.db_connection.password << "\n";

    std::cout << this->search_settings.search_depth << "\n";
    std::cout << this->search_settings.word_length_min << "\n";
    std::cout << this->search_settings.word_length_max << "\n";

    std::cout << this->search_settings.thread_max << "\n";
}
