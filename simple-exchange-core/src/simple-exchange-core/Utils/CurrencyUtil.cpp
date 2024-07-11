#include "simple-exchange-core/Utils/CurrencyUtil.hpp"
#include <cmath>

std::string CurrencyUtil::getCurCodeStr(cur_t aCurType)
{
    const static curcode_map_t curCodesMap = 
        {
            {   CURRENCY_TYPE::NONE    ,    "NONE"  },
            {   CURRENCY_TYPE::USD     ,    "USD"   },
            {   CURRENCY_TYPE::RUB     ,    "RUB"   },
        };

        const auto it = curCodesMap.find(aCurType);
        if (it != curCodesMap.end()) 
        {
            return it->second;
        }

        return "NOT FOUND!";
}

ldouble CurrencyUtil::round2(ldouble aValue)
{
    return std::round(aValue * 100.0) / 100.0;
}