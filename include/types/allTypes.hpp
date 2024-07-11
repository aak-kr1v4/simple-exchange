#ifndef ALLTYPES_HPP
#define ALLTYPES_HPP

#include <unordered_map>
#include <string>

#include "currencyTypes.hpp"
#include "requestTypes.hpp"
#include "orderTypes.hpp"

class User;

using balance_map_t = std::unordered_map<CUR_T ,  ldouble>;
using curcode_map_t = std::unordered_map<CUR_T ,  std::string>;
using users_map_t   = std::unordered_map<size_t,  User>;

#endif