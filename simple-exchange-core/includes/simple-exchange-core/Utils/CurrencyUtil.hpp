#ifndef CURRENCY_UTIL_HPP
#define CURRENCY_UTIL_HPP

#include "types/allTypes.hpp"

class CurrencyUtil
{
    public:
        CurrencyUtil() = delete;

    public:
        static std::string getCurCodeStr(CUR_T aCurType);
        static ldouble     round2(ldouble aValue); // round to two decimal plac>

};

#endif