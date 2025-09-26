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

    // Инициализация пула рабочих потоков
    this->work_pool = std::make_unique<ThreadPool>(); // ThreadPool заинициализирует рабочие потоки
    // ThreadPool использует количество потоков согласно std::thread::hardware_concurrency()
    std::cout << "Initialized ThreadPool with " << work_pool->getCPUcount() << " threads" << std::endl;

    // Инициализация пула соединений с базой данных
    DatabaseManager::Config db_config(this->search_settings.db_connection);
    this->db_pool_ = std::make_unique<DatabasePool>(db_config, 2); // 2 рабочих потока для базы данных
    !this->db_pool_ ? throw std::runtime_error("Failed to initialize Database Pool") : std::cout << "Database Pool initialized successfully\n" << std::endl;

}

webCrawler::~webCrawler()
{
    stopCrawling(); // а деструктор ThreadPool соединит потоки
    if (db_pool_) {
        db_pool_->shutdown(); // Ждем оконачание работы с базой данных
    }
    std::cout << "Crawling completed!" << std::endl;
}

void webCrawler::startCrawling()
{
    if (is_running.load()) {
        std::cout << "!!!...Crawler is already running...!!!" << std::endl;
        return;
    }
    
    is_running.store(true);
    should_stop.store(false);
    
    std::cout << "\n=== Starting web crawling ===";
    std::cout << "\nInitial conditions: ";
    std::cout << "\n  should_stop: " << should_stop.load();
    std::cout << "\n  active_workers: " << active_workers.load();
    std::cout << "\n  Max depth: " << search_settings.search_depth_max;
    std::cout << "\n  Max pages: " << search_settings.max_pages;
    std::cout << "\n  start URL: " << search_settings.url.url_link_info->link << "\n";
    std::cout << std::endl;
    
    // Добавляем начальную ссылку в очередь ссылок
    UrlInfo initial_url(this->search_settings.url.url_link_info, 0);
    pending_urls.push(initial_url);
    pending_count++;
    
    // Рабочий цикл используя ThreadPool
    while   (   !should_stop.load() &&                                      // Пока НЕ сказано остановиться
                (active_workers.load() > 0 || pending_count.load() > 0) &&  // Пока рабочих больше 0 и добавленых строк больше 0
                total_pages_crawled.load() < search_settings.max_pages      // Пока НЕ достигли предела по количества обработанных страниц
            ) 
    {   
    // std::cout << "\n\nshould_stop: " << should_stop.load()
    //     << "\tactive_workers: " << active_workers.load()
    //     << "\tpending_count: " << pending_count.load()
    //     << "\tpages_crawled: " << total_pages_crawled.load() << std::endl;

        UrlInfo url_data;
        if (pending_urls.pop(url_data)) { // Если в очереди ссылок есть ссылки, то передаем из стопки в url_data 
            pending_count--; 
            std::cout << "\nProcessing URL: " << url_data.url_link_info->link << std::endl;
                        
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
            if (active_workers.load() == 0 && pending_urls.empty()) {
                std::cout << "\n!!! EXIT CONDITION: !!!" << std::endl;
                if (active_workers.load() == 0) std::cout << "no active workers\n";
                if (pending_urls.empty()) std::cout << "no pending urls\n" << std::endl;
                break; // Нет активных работающих и нет работы - выходим из цикла
            }
           // Нет задач, короткое ожидание
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        // std::cout << "Worker loop finished in startCrawling()" << std::endl; 
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // without sleep premature destructor call. why? who knows.
    
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
    try {
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
            should_stop.store(true);
            return;
        }
    
        // Загрузка страницы
        HTTPUtils::Config config;
        std::string content = HTTPUtils::fetchPage(url_data.url_link_info.value(), config).value();
    
        if (content.empty()) {
            std::cout << "Failed to download: " << url_data.url_link_info->adress << std::endl;
            return;
        }
    
        
        // Обработка страницы в структуру ParsedContent, в которой есть отформатированные ссылки и текст со станицы
        auto parsed_content = HtmlParser::processHtml(content, url_data.url_link_info.value(), url_data.search_depth);
        
        TextIndexer indexer; // Индексация слов
        indexer.indexContent(parsed_content->body_text); 
        
        CrawlResult data_for_database = {
            url_data.url_link_info->adress, 
            parsed_content->page_title, 
            parsed_content->body_text, 
            indexer.getWordFrequenciesSorted()
        };
    
        // Добавление результата в очередь на запись в базу данных
        db_pool_->queueResult(data_for_database);
        
        total_pages_crawled++;
        total_words_indexed =+ data_for_database.word_frequencies.size();
    
        std::cout << "\nCompleted: " << url_data.url_link_info->link 
                << "\n(total pages crawled: " << total_pages_crawled.load() << ")"
                << std::endl;    
    
    
        // Добавление извлеченных ссылок в очердь ссылок если не достигли максимальной глубины поиска    
        {   
            std::lock_guard<std::mutex> lock(visited_mutex);
            if (url_data.search_depth < search_settings.search_depth_max) {
                for (const auto& link : parsed_content->discovered_urls) {
                    if (visited_urls.find(link.url_link_info->adress) == visited_urls.end()) {
                        pending_urls.push(link);
                        pending_count++;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << "\nEXEPTION in crawl url: " << e.what() << std::endl;
        throw;
    }
}