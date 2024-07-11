#ifndef CURRENCY_TYPES_HPP
#define CURRENCY_TYPES_HPP

#include "commonTypes.hpp"

enum class CURRENCY_TYPE : ushort
{
    NONE = 0,
    RUB,
    USD,
    END_OF_ENUM
};

using CUR_T = CURRENCY_TYPE;

#endif