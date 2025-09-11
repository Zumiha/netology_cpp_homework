#include "HtmlParser.h"

#include <regex>
#include <algorithm>
#include <cctype>
#include <unordered_set>
#include <unordered_map>
#include <cstdio>


std::string HtmlParser::decodeHtmlEntities(const std::string &text)
{
static const std::unordered_map<std::string, std::string> html_entities = {
        {"&amp;", "&"},
        {"&lt;", "<"},
        {"&gt;", ">"},
        {"&quot;", "\""},
        {"&apos;", "'"},
        {"&#39;", "'"},
        {"&nbsp;", " "},
        {"&copy;", "©"},
        {"&reg;", "®"},
        {"&trade;", "™"},
        {"&hellip;", "…"},
        {"&mdash;", "—"},
        {"&ndash;", "–"},
        {"&lsquo;", "'"},
        {"&rsquo;", "'"},
        {"&ldquo;", "\""},
        {"&rdquo;", "\""},
        {"&bull;", "•"}
    };
    
    std::string result = text;
    
    // Заменяем сущности
    for (const auto& entity : html_entities) {
        size_t pos = 0;
        while ((pos = result.find(entity.first, pos)) != std::string::npos) {
            result.replace(pos, entity.first.length(), entity.second);
            pos += entity.second.length();
        }
    }
    
    // Обработка числовых сущностей (&#123; и &#x1A;)
    std::regex numeric_entity_regex(R"(&#([0-9]+);)");
    std::regex hex_entity_regex(R"(&#x([0-9A-Fa-f]+);)");
    
    // Десятичные числовые сущности
    result = std::regex_replace(result, numeric_entity_regex, [](const std::smatch& match) {
        try {
            int code = std::stoi(match[1].str());
            if (code > 0 && code < 127) {  // Базовый ASCII
                return std::string(1, static_cast<char>(code));
            }
            return match.str();
        } catch (...) {
            return match.str();
        }
    });
    
    // Шестнадцатеричные числовые сущности
    result = std::regex_replace(result, hex_entity_regex, [](const std::smatch& match) {
        try {
            int code = std::stoi(match[1].str(), nullptr, 16);
            if (code > 0 && code < 127) {  // Базовый ASCII
                return std::string(1, static_cast<char>(code));
            }
            return match.str();
        } catch (...) {
            return match.str();
        }
    });
    
    return result;
}

std::string HtmlParser::normalizeText(const std::string& text) {
    std::string result = text;
    
    // Заменить несколько пробелов одним пробелом
    std::regex whitespace_regex(R"(\s+)", std::regex_constants::optimize);
    result = std::regex_replace(result, whitespace_regex, " ");
    
    // Удаление пробелов в начале и конце
    const auto not_space = [](unsigned char c) { return !std::isspace(c); };
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), not_space));
    result.erase(std::find_if(result.rbegin(), result.rend(), not_space).base(), result.end());
    
    return result;
}


std::string HtmlParser::extractBodyText(const std::string& html) {
    std::string result = html;
    
    // Удалить скрипт и стилевое содержимое (включая теги)
    std::regex script_style_regex(R"(<(script|style)[^>]*>.*?</\1>)", std::regex_constants::icase | std::regex_constants::optimize);
    result = std::regex_replace(result, script_style_regex, " ");
    
    // Удалить HTML-комментарии
    std::regex comment_regex(R"(<!--.*?-->)", std::regex_constants::optimize);
    result = std::regex_replace(result, comment_regex, " ");
    
    // Удалить все HTML-теги
    std::regex tag_regex(R"(<[^>]*>)", std::regex_constants::optimize);
    result = std::regex_replace(result, tag_regex, " ");
    
    // Декодирование HTML
    return normalizeText(decodeHtmlEntities(result));
}

std::vector<std::string> HtmlParser::extractLinks(const std::string& html) {
    std::vector<std::string> links;
    std::unordered_set<std::string> unique_links; // Упразднение дубликатов
    
    // Регулярное выражение для поиска атрибутов href в тегах <a>
    std::regex link_regex(R"(<a[^>]*href\s*=\s*[\"']([^\"']+)[\"'][^>]*>)", std::regex_constants::icase | std::regex_constants::optimize);
    
    std::sregex_iterator iter(html.begin(), html.end(), link_regex);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        std::string link = iter->str(1); // Первая группа 
        
        // Базовая проверка и нормализация ссылок
        if (!link.empty() && link[0] != '#' && link.find("javascript:") != 0) {
            // Удаление фрагментов из URL-адресов
            size_t fragment_pos = link.find('#');
            if (fragment_pos != std::string::npos) {
                link = link.substr(0, fragment_pos);
            }
            
            // Добавлять только в том случае, если еще не добавлено
            if (unique_links.find(link) == unique_links.end()) {
                unique_links.insert(link);
                links.push_back(link);
            }
        }
    }
    
    return links;
}

std::string HtmlParser::getTitle(const std::string& html) {
    std::regex title_regex("<title[^>]*>([^<]*)</title>", std::regex_constants::icase);
    std::smatch matches;
    
    if (std::regex_search(html, matches, title_regex)) {
        std::string title = matches[1].str();
        
        title = decodeHtmlEntities(title);        
        title = normalizeText(title); 
        return title;
    }
    
    return "";  // Возвращаем пустую строку, если заголовок не найден
}

std::optional<ParsedContent> HtmlParser::processHtml(const std::optional<std::string>& html_content, const Link& base_link, int search_depth) {
    if (!html_content.has_value() || html_content->empty()) {
        return std::nullopt;
    }
    
    const std::string& html = html_content.value();
        
    return ParsedContent{
        .page_link = base_link.adress,
        // Извлечение заголовока страницы
        .page_title = getTitle(html),
        // Преобразование в абсолютные URL-адреса и создание объектов UrlInfo
        .discovered_urls = resolveUrls(result.raw_links, base_link, search_depth + 1),
        // Извлечение ссылок (перед удалением тегов)
        .raw_links = extractLinks(html),
        // Извлечение и очистка текста
        .body_text = extractBodyText(html)
    };
}

std::vector<UrlInfo> HtmlParser::resolveUrls(const std::vector<std::string>& links, const Link& base_link, int search_depth) {
    std::vector<UrlInfo> resolved_urls;
    resolved_urls.reserve(links.size());
    
    // Восстановить базовый URL из структуры ссылки
    std::string base_url = (base_link.protocol == ProtocolType::HTTPS ? "https://" : "http://") + base_link.hostName + base_link.query;
    
    for (const auto& link : links) {
        std::string absolute_url;
        
        if (link.find("http://") == 0 || link.find("https://") == 0) {
            // Абсолютный URL
            absolute_url = link;
        } else if (link.find("//") == 0) {
            // URL, относительный к протоколу
            std::string protocol = (base_link.protocol == ProtocolType::HTTPS) ? "https" : "http";
            absolute_url = protocol + ":" + link;
        } else if (link[0] == '/') {
            // URL, относительный к корневой
            std::string domain = (base_link.protocol == ProtocolType::HTTPS ? "https://" : "http://") + base_link.hostName;
            absolute_url = domain + link;
        } else {
            // Относительный URL
            std::string base_path = (base_link.protocol == ProtocolType::HTTPS ? "https://" : "http://") + base_link.hostName + base_link.query;
            size_t last_slash = base_path.find_last_of('/');
            if (last_slash != std::string::npos) {
                base_path = base_path.substr(0, last_slash + 1);
            }
            absolute_url = base_path + link;
        }
        
        // Создание UrlInfo с помощью строкового конструктора
        UrlInfo url_info(absolute_url, search_depth);
        
        // Добавляем только в случае успешного парсинга
        if (url_info.url_link_info.has_value()) {
            resolved_urls.push_back(url_info);
        }
    }
    
    return resolved_urls;
}