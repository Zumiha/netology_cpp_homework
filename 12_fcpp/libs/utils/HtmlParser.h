#pragma once

#include <string>
#include <vector>
#include <optional>
#include "UrlParser.h"

#include "struct.h"

struct ParsedContent {
    std::string page_link;                    // Ссылка обрабатываемой страницы 
    std::string page_title;                   // Название страницы 
    std::vector<UrlInfo> discovered_urls;     // URLs found in the HTML, ready for crawling
    std::vector<std::string> raw_links;       // Oригинальные ссылки (для статистики, дебагинга и пр.)
    std::string body_text;
};

class HtmlParser {
private:
    static std::string decodeHtmlEntities(const std::string& text);
    static std::string normalizeText(const std::string& text);

    static std::string extractBodyText(const std::string& html);
    static std::vector<std::string> extractLinks(const std::string& html);
    static std::string HtmlParser::getTitle(const std::string& html);
public:
    static std::optional<ParsedContent> processHtml(const std::optional<std::string>& html_content, const Link& base_link, int search_depth = 1);
    static std::vector<UrlInfo> resolveUrls(const std::vector<std::string>& links, const Link& base_link, int search_depth = 1);
};