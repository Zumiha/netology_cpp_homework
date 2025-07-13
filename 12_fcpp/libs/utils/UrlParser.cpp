#include "UrlParser.h"

#include <regex>
#include <algorithm>
#include <cctype>


std::optional<Link> URLParser::parse(const std::string &url)
{
    if (url.empty()) {
        return std::nullopt;
    }
    
    const std::regex urlRegex(R"(^(https?)://([^/]+)(/?.*)$)");
    std::smatch match;
    
    if (!std::regex_match(url, match, urlRegex)) {
        return std::nullopt;
    }

    Link link;

    std::string protocol = match[1].str();
    std::transform(protocol.begin(), protocol.end(), protocol.begin(), ::tolower);

    if (protocol == "http") {
        link.protocol = ProtocolType::HTTP;
    } else if (protocol == "https") {
        link.protocol = ProtocolType::HTTPS;
    } else {
        return std::nullopt;
    }

    link.hostName = match[2].str();
    size_t portPos = link.hostName.find(':');
    if (portPos != std::string::npos) {
        link.hostName = link.hostName.substr(0, portPos);
    }
    std::transform(link.hostName.begin(), link.hostName.end(), link.hostName.begin(), ::tolower);

    link.query = match[3].str();
    if (link.query.empty()) {
        link.query = "/";
    }
    
    return link;
}
