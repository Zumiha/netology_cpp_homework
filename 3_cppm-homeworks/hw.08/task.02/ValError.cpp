#include "ValError.h"

ValExcept::ValExcept(std::string const& err) : std::domain_error(err) {}