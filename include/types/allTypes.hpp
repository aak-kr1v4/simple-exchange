#ifndef ALLTYPES_HPP
#define ALLTYPES_HPP

#include "currencyTypes.hpp"
#include <unordered_map>
#include <string>

using balance_map_t = std::unordered_map<cur_t, ldouble>;
using curcode_map_t = std::unordered_map<cur_t, std::string>;

#endif