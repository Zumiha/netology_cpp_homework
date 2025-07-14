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
	std::string link;		// Неотформатированный вид ссылки
	ProtocolType protocol;	
	std::string hostName;	// Имя хоста - адрес домена 
	std::string query;		// Адрес идущий после домена
	std::string adress;		// Отформатированный вид ссылки

	bool operator==(const Link& l) const
	{
		return protocol == l.protocol
			&& hostName == l.hostName
			&& query == l.query
			&& link == l.link
			&& adress == l.adress;
	}

	Link& operator=(const Link& l) { // а нужно ли это если есть std::optional<Link> ?
		if (this == &l) return *this;

		protocol = l.protocol;
		hostName = l.hostName;
		query = l.query;
		link = l.link;
		adress = l.adress;	
	}
};

class URLParser {
public:
    // Парсим URL строку в структуру 
    static std::optional<Link> parse(const std::string& url);
};