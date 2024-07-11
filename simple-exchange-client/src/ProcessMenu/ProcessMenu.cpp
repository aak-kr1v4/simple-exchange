#include "ProcessMenu.hpp"
#include "simple-exchange-core/Utils/CurrencyUtil.hpp"
#include <iostream>

ORDER_T ProcessMenu::inputOrderType()
{
    std::cout << "Order Type: \n"
                 "1) Buy\n"
                 "2) Sell\n"
              << std::endl;

    short menu_option_num;
    std::cin >> menu_option_num;

    switch (menu_option_num) 
    {
        case 1:
            return ORDER_T::BUY;
        case 2:
            return ORDER_T::SELL;
        default:
            std::cout << "Unknown order type\n" << std::endl;
            return ORDER_T::NONE;
    }
}

CUR_T ProcessMenu::inputCurrencyType(bool aIsBase, CUR_T aExcludedCurT)
{
    aIsBase ? std::cout << "Input Base Currency Type:\n" : std::cout << "Input Quote Currency Type:\n";

    ushort curSeqNum = 1; // currency sequence number
    std::unordered_map<ushort, ushort> seqNumToRealNum;

    for (ushort i = 1; i < static_cast<ushort>(CUR_T::END_OF_ENUM); ++i) 
    {
        CUR_T curT = static_cast<CUR_T>(i);

        if (curT != aExcludedCurT)
        {
            seqNumToRealNum[curSeqNum] = i;
            std::cout << curSeqNum++ << ") " << CurrencyUtil::getCurCodeStr(curT) << "\n";
        }
    }

    short menu_option_num;
    std::cin >> menu_option_num;

    if (menu_option_num >= 1 && menu_option_num < static_cast<ushort>(CUR_T::END_OF_ENUM)) 
    {
        return static_cast<CUR_T>(seqNumToRealNum[menu_option_num]);
    } 
    else 
    {
        std::cout << "Unknown currency type\n" << std::endl;
        return CUR_T::NONE;
    }
}

ldouble ProcessMenu::inputAndRoundValue(bool aIsBase)
{
    aIsBase ? std::cout << "Enter Base value: " : std::cout << "Enter Quote value: "; 
    ldouble value;
    std::cin >> value;
    return CurrencyUtil::round2(value);
}

bool ProcessMenu::inputOrderCreate(nlohmann::json &aOrderData)
{
    ORDER_T orderType = inputOrderType();
    if (orderType == ORDER_T::NONE) return false;

    CUR_T baseCurT = inputCurrencyType();
    if (baseCurT == CUR_T::NONE) return false;

    ldouble baseValue = inputAndRoundValue();

    CUR_T quoteCurT = inputCurrencyType(false, baseCurT);
    if (quoteCurT == CUR_T::NONE) return false;

    ldouble quoteValue = inputAndRoundValue(false);

    aOrderData["OrderData"] = 
    {
        {   "OrderT",           orderType   },
        {   "BaseCurT",         baseCurT    },
        {   "BaseValue",        baseValue   },
        {   "QuoteCurT",        quoteCurT   },
        {   "QuoteValue",       quoteValue  }
    };

    return true;
}
