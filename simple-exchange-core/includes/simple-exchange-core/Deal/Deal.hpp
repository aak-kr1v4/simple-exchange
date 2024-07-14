#ifndef DEAL_HPP
#define DEAL_HPP

#include "types/allTypes.hpp"

struct Deal
{
    ldouble dealBase;
    ldouble dealBaseInQuoteCurT;

    CUR_T baseCurT;
    CUR_T quoteCurT;
    
    size_t buyerId;
    size_t sellerId;
};

#endif