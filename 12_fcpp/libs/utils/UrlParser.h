#pragma once
#include <string>
#include <vector>
#include <optional>

enum class ProtocolType
{
	HTTP = 0,
	HTTPS = 1
};

struct Link
{
	ProtocolType protocol;
	std::string hostName;
	std::string query;

	bool operator==(const Link& l) const
	{
		return protocol == l.protocol
			&& hostName == l.hostName
			&& query == l.query;
	}
};

class URLParser {
public:
    // Парсим URL строку в структуру 
    static std::optional<Link> parse(const std::string& url);
};