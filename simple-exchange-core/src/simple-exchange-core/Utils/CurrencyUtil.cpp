#include "simple-exchange-core/Utils/CurrencyUtil.hpp"
#include <cmath>

std::string CurrencyUtil::getCurCodeStr(CUR_T aCurType)
{
    const static curcode_map_t curCodesMap = 
        {
            {   CUR_T::NONE ,    "NONE"  },
            {   CUR_T::USD  ,    "USD"   },
            {   CUR_T::RUB  ,    "RUB"   },
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