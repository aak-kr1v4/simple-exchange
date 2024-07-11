#ifndef ORDER_TYPES_HPP
#define ORDER_TYPES_HPP

#include "commonTypes.hpp"

enum class ORDER_TYPE: uchar
{
    NONE = 0,
    BUY,
    SELL, 
    END_OF_ENUM
};

using ORDER_T = ORDER_TYPE;
#endif