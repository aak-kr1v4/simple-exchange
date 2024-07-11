#ifndef ORDER_HPP
#define ORDER_HPP

#include "types/allTypes.hpp"

class Order
{
    using ldouble = long double;

    public:
        Order(  ORDER_T aOrderT, CUR_T aBaseCurT, CUR_T aQuoteCurT, 
                ldouble aBase, ldouble aQuote, size_t  aUserId
            );

    public:
        void        setBase         (ldouble aBase);
        ldouble     getBase         ()     const;

        ldouble     getQuote        ()     const;

        ORDER_T     getOrderType    ()     const;
        size_t      getOwnerId      ()     const;
        
    public:
        bool operator<(const Order& aOther) const;

    private:
        ORDER_T     mOrderType;

        ldouble     mBase;
        CUR_T       mBaseCurT;

        ldouble     mQuote;
        CUR_T       mQuoteCurT;

        size_t      mOwnerId;

};

#endif
