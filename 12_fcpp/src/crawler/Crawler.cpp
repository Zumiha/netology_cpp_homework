#include "Crawler.h"


webCrawler::webCrawler(int argc, char* argv[])
{   
    if (argv == nullptr || argc < 2) {
        this->parser = std::make_unique<IniParser>(ini_file_name); std::cout << "created object with default file\n";
    } else {
        std::string def = argv[1];
        if (argc > 1 && def == "-cf") {
            this->parser = std::make_unique<IniParser>(argv[2]);
            std::cout << "created object with declared file\n";
        }
    }
    this->setSearchSettings();

    // Initialize thread pool
    this->work_pool = std::make_unique<ThreadPool>(); // ThreadPool заинициализирует рабочие потоки
    // ThreadPool using number of threads according to std::thread::hardware_concurrency()
    std::cout << "Initialized ThreadPool with " << std::thread::hardware_concurrency() << " threads" << std::endl;
}

webCrawler::~webCrawler()
{
    stopCrawling();
    // а деструктор ThreadPool соединит потоки
    std::cout << "Crawling completed!" << std::endl;
}

void webCrawler::startCrawling()
{
    if (is_running.load()) {
        std::cout << "Crawler is already running!" << std::endl;
        return;
    }
    
    is_running.store(true);
    should_stop.store(false);
    
    std::cout << "Starting web crawling..." << std::endl;
    std::cout << "Initial URL: " << search_settings.url.url_link_info->link << std::endl;
    std::cout << "Max depth: " << search_settings.search_depth_max << std::endl;
    std::cout << "Max pages: " << search_settings.max_pages << "\n" << std::endl;
    
    // Добавляем начальную ссылку в очередь ссылок
    UrlInfo initial_url(this->search_settings.url.url_link_info, 0);
    pending_urls.push(initial_url);
    {
        std::lock_guard<std::mutex> lock(count_mutex);
        pending_count++;
    }
    
    // Рабочий цикл используя ThreadPool
    while   (   !should_stop.load() &&                                      // Пока НЕ сказано остановиться
                (active_workers.load() > 0 || pending_count.load() > 0) &&  // Пока рабочих больше 0 и добавленых строк больше 0
                total_pages_crawled.load() < search_settings.max_pages      // Пока НЕ достигли предела по количества обработанных страниц
            ) 
    {        
        UrlInfo url_data;
        if (pending_urls.pop(url_data)) { // Если в очереди ссылок есть ссылки, то передаем из стопки в url_data 
            {
                std::lock_guard<std::mutex> lock(count_mutex);
                pending_count--;
            }
            
            // Добавляем задачи краулера в ThreadPool
            work_pool->submit([this, url_data]() {
                active_workers++;
                try {
                    crawlUrl(url_data);
                } catch (const std::exception& e) {
                    std::cerr << "Error crawling " << url_data.url_link_info->link << ": " << e.what() << std::endl;
                }
                active_workers--;
            });
        } else {
            // Если нет работы, проверяем нужно ли продолжать
            if (active_workers.load() == 0) {
                break; // Нет активных работающих и нет работы - выходим из цикла
            }
           // Нет задач, короткое ожидание
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // without sleep premature destructor call. why? who knows.

        // std::cout << "\nshould stop? - " << should_stop.load();
        // std::cout << "\nactive workers: " << active_workers.load();
        // {
        //     std::lock_guard<std::mutex> lock(count_mutex);
        //     std::cout << "\npending count: " << pending_count.load();
        // }
        // std::cout << "\npage limit?: " << (total_pages_crawled.load() > search_settings.max_pages);
        // std::cout << std::endl;

    }
    
    // Wait for all active workers to finish
    while (active_workers.load() > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    is_running.store(false);
    
}

void webCrawler::stopCrawling()
{  
    should_stop.store(true);
    is_running.store(false);

    // std::cout << "\n\nText from pages:\n";
    // bool queue_not_empty = {true};
    // int i = 0;
    // std::string text;
    // while (queue_not_empty) {   
    //     queue_not_empty = page_text.pop(text);
    //     if (!queue_not_empty) break;
    //     i++;
    //     std::cout << "\nPage " << i << " text:\n";
    //     std::cout << text << std::endl;
    // } 
}

void webCrawler::printSettings()
{
    std::cout << "\n";
    std::cout << this->search_settings.url.url_link_info->link << "\n";

    std::cout << this->search_settings.db_connection.host << "\n";
    std::cout << this->search_settings.db_connection.port << "\n";
    std::cout << this->search_settings.db_connection.dbname << "\n";
    std::cout << this->search_settings.db_connection.user << "\n";
    std::cout << this->search_settings.db_connection.password << "\n";

    std::cout << this->search_settings.search_depth_max << "\n";
    std::cout << this->search_settings.word_length_min << "\n";
    std::cout << this->search_settings.word_length_max << "\n";

    std::cout << this->search_settings.thread_max << "\n";
}

void webCrawler::setSearchSettings()
{
    this->search_settings.url.url_link_info = URLParser::parse(this->parser->getValue<std::string>("url.urltest"));
    this->search_settings.search_depth_max = this->parser->getValue<int>("indexing.search_depth");


    this->search_settings.db_connection.host = this->parser->getValue<std::string>("db.host");
    this->search_settings.db_connection.port = this->parser->getValue<std::string>("db.port");
    this->search_settings.db_connection.dbname = this->parser->getValue<std::string>("db.dbname");
    this->search_settings.db_connection.user = this->parser->getValue<std::string>("db.user");
    this->search_settings.db_connection.password = this->parser->getValue<std::string>("db.password");
    
    this->search_settings.word_length_min = this->parser->getValue<int>("indexing.word_length_min");
    this->search_settings.word_length_max = this->parser->getValue<int>("indexing.word_length_max");
    this->search_settings.max_pages = this->parser->getValue<int>("indexing.max_pages");

    this->search_settings.thread_max = this->parser->getValue<int>("threading.thread_max");
}

void webCrawler::crawlUrl(UrlInfo url_data)
{
    // auto url_link = URLParser::parse(url_data.address); // Parsing link to std::optional<Link> used as struct Link
    std::cout << "Starting to crawl: " << url_data.url_link_info->link << " (depth: " << url_data.search_depth << ")" << std::endl;
    
    // Проверяем посетили ли уже ссылку
    {   
        std::lock_guard<std::mutex> lock(visited_mutex);
        if (visited_urls.find(url_data.url_link_info->adress) != visited_urls.end()) { 
            std::cout << "Already visited: " << url_data.url_link_info->adress << " - skipping" << std::endl;
            return;
        }
        visited_urls.insert(url_data.url_link_info->adress); // Добавляем в посещенные ссылки
    }

    // Проверяем ограничение по страницам
    if (total_pages_crawled.load() >= search_settings.max_pages) {
        std::cout << "Reached maximum pages limit" << std::endl;
        return;
    }

    // Загрузка страницы
    HTTPUtils::Config config;
    std::string content = HTTPUtils::fetchPage(url_data.url_link_info.value(), config).value();

    if (content.empty()) {
        std::cout << "Failed to download: " << url_data.url_link_info->adress << std::endl;
        return;
    }

    total_pages_crawled++;
    
    // Обработка страницы в структуру ParsedContent, в которой есть отформатированные ссылки и текст со станицы
    auto parsed_content = HtmlParser::processHtml(content, url_data.url_link_info.value(), url_data.search_depth);

    std::vector<UrlInfo> new_links = parsed_content->discovered_urls; // links to add 
    page_text.push(parsed_content->body_text); // text extracted from page add to safequeue

    std::cout << "Completed: " << url_data.url_link_info->link << " (pages: " << total_pages_crawled.load() << ")" << std::endl;
    std::cout << "Total pages crawled: " << total_pages_crawled.load() << std::endl;
    std::cout << "Total words indexed: " << total_words_indexed.load() << std::endl;    


    // Добавление извлеченных ссылок в очердь ссылок если не достигли максимальной глубины поиска    
    {   
        std::lock_guard<std::mutex> lock(visited_mutex);
        if (url_data.search_depth < search_settings.search_depth_max) {
            for (const auto& link : new_links) {
                if (visited_urls.find(link.url_link_info->adress) == visited_urls.end()) {
                    pending_urls.push(link);
                    std::lock_guard<std::mutex> lock(count_mutex);
                    pending_count++;
                    std::cout << "pending urls count: " << pending_count.load() << std::endl;
                }
            }
        }
    }

    std::cout << "check pending url size: " << pending_urls.size() << std::endl;
    std::cout << "check pending url empty: " << pending_urls.empty() << std::endl;
    std::cout << std::endl;

}

void webCrawler::indexWords(const std::string& content, const std::string& url) 
{
    // Код индексирования слов на странице
}
