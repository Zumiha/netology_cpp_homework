#pragma once
#include <stdexcept>

class ValExcept : public std::domain_error {
public:
	ValExcept(std::string const& err);
};