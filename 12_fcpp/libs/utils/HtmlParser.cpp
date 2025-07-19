#include "HtmlParser.h"

#include <regex>
#include <algorithm>
#include <cctype>
#include <unordered_set>
#include <cstdio>

std::string HtmlParser::stripHtmlTags(const std::string& html) {
    std::string result = html;
    
    // Remove script and style content (including tags)
    std::regex script_style_regex(R"(<(script|style)[^>]*>.*?</\1>)", std::regex_constants::icase | std::regex_constants::optimize);
    result = std::regex_replace(result, script_style_regex, " ");
    
    // Remove HTML comments
    std::regex comment_regex(R"(<!--.*?-->)", std::regex_constants::optimize);
    result = std::regex_replace(result, comment_regex, " ");
    
    // Remove all HTML tags
    std::regex tag_regex(R"(<[^>]*>)", std::regex_constants::optimize);
    result = std::regex_replace(result, tag_regex, " ");
    
    // Decode common HTML entities
    result = std::regex_replace(result, std::regex("&amp;"), "&");
    result = std::regex_replace(result, std::regex("&lt;"), "<");
    result = std::regex_replace(result, std::regex("&gt;"), ">");
    result = std::regex_replace(result, std::regex("&quot;"), "\"");
    result = std::regex_replace(result, std::regex("&apos;"), "'");
    result = std::regex_replace(result, std::regex("&nbsp;"), " ");
    
    return result;
}

std::string HtmlParser::normalizeText(const std::string& text) {
    std::string result = text;
    
    // Replace multiple whitespace with single space
    std::regex whitespace_regex(R"(\s+)", std::regex_constants::optimize);
    result = std::regex_replace(result, whitespace_regex, " ");
    
    // Trim leading and trailing whitespace
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), result.end());
    
    return result;
}

std::vector<std::string> HtmlParser::extractLinks(const std::string& html) {
    std::vector<std::string> links;
    std::unordered_set<std::string> unique_links; // Avoid duplicates
    
    // Regex to match href attributes in <a> tags
    std::regex link_regex(R"(<a[^>]*href\s*=\s*[\"']([^\"']+)[\"'][^>]*>)", std::regex_constants::icase | std::regex_constants::optimize);
    
    std::sregex_iterator iter(html.begin(), html.end(), link_regex);
    std::sregex_iterator end;
    
    for (; iter != end; ++iter) {
        std::string link = iter->str(1); // First capture group
        
        // Basic link validation and normalization
        if (!link.empty() && link[0] != '#' && link.find("javascript:") != 0) {
            // Remove fragments from URLs
            size_t fragment_pos = link.find('#');
            if (fragment_pos != std::string::npos) {
                link = link.substr(0, fragment_pos);
            }
            
            // Only add if not already present
            if (unique_links.find(link) == unique_links.end()) {
                unique_links.insert(link);
                links.push_back(link);
            }
        }
    }
    
    return links;
}

std::optional<ParsedContent> HtmlParser::processHtml(const std::optional<std::string>& html_content, const Link& base_link, int search_depth) {
    if (!html_content.has_value() || html_content->empty()) {
        return std::nullopt;
    }
    
    const std::string& html = html_content.value();
    
    ParsedContent result;
    
    // Extract links first (before removing tags)
    result.raw_links = extractLinks(html);

    auto next_depth = search_depth + 1;
    // Resolve to absolute URLs and create UrlInfo objects
    result.discovered_urls = resolveUrls(result.raw_links, base_link, next_depth);
    
    // Extract and clean body text
    std::string text = stripHtmlTags(html);
    result.body_text = normalizeText(text);
    result.page_link = base_link.adress;

    return result;
}

std::vector<UrlInfo> HtmlParser::resolveUrls(const std::vector<std::string>& links, const Link& base_link, int search_depth) {
    std::vector<UrlInfo> resolved_urls;
    resolved_urls.reserve(links.size());
    
    // Reconstruct base URL from Link structure
    std::string base_url = (base_link.protocol == ProtocolType::HTTPS ? "https://" : "http://") + base_link.hostName + base_link.query;
    
    for (const auto& link : links) {
        std::string absolute_url;
        
        if (link.find("http://") == 0 || link.find("https://") == 0) {
            // Absolute URL
            absolute_url = link;
        } else if (link.find("//") == 0) {
            // Protocol-relative URL
            std::string protocol = (base_link.protocol == ProtocolType::HTTPS) ? "https" : "http";
            absolute_url = protocol + ":" + link;
        } else if (link[0] == '/') {
            // Root-relative URL
            std::string domain = (base_link.protocol == ProtocolType::HTTPS ? "https://" : "http://") + base_link.hostName;
            absolute_url = domain + link;
        } else {
            // Relative URL
            std::string base_path = (base_link.protocol == ProtocolType::HTTPS ? "https://" : "http://") + base_link.hostName + base_link.query;
            size_t last_slash = base_path.find_last_of('/');
            if (last_slash != std::string::npos) {
                base_path = base_path.substr(0, last_slash + 1);
            }
            absolute_url = base_path + link;
        }
        
        // Create UrlInfo using the string constructor (which will parse via URLParser)
        UrlInfo url_info(absolute_url, search_depth);
        
        // Only add if parsing was successful
        if (url_info.url_link_info.has_value()) {
            resolved_urls.push_back(url_info);
        }
    }
    
    return resolved_urls;
}