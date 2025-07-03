#include <memory>
#include "IniParser.h"
#include "ThreadPool.h"

struct DbInfo {
    std::string host;
    std::string port;
    std::string dbname;
    std::string user;
    std::string password;
};

struct CrawlParams
{
    DbInfo db_connection;
	std::string url;
	int	search_depth = 1;
	int	word_length_min = 3;
	int	word_length_max = 32;
	int thread_max = 0;
};


class webCrawler {
public:
    webCrawler(int argc, char* argv[]);
    ~webCrawler();
    void runSearch();
    
    void printSettings();

protected:
    void setSearchSettings();

private:
    CrawlParams search_settings;
    std::unique_ptr<IniParser> parser;
    std::string ini_file_name = "crawlerdata.ini";
};