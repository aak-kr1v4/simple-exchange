#ifndef PROCESS_MENU_HPP
#define PROCESS_MENU_HPP

#include "types/allTypes.hpp"
#include "nlohmann/json.hpp"

class ProcessMenu
{
    public:
        static ORDER_T  inputOrderType();
        static CUR_T    inputCurrencyType(bool aIsBase = true, CUR_T aExcludedCurT = CUR_T::END_OF_ENUM);
        static ldouble  inputAndRoundValue(bool aIsBase = true);
        static bool     inputOrderCreate(nlohmann::json& aOrderData);

};

#endif