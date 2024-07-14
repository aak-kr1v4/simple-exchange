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
        Order();

    public:
        void        setBase         (ldouble aBase);
        ldouble     getBase         ()  const;

        ldouble     getQuote        ()  const;
        void        setQuote        (ldouble aQuote);

        ORDER_T     getOrderType    ()  const;
        void        setOrderType    (ORDER_T aOrderT);

        size_t      getOwnerId      ()  const;
        void        setOwnerId      (size_t aOwnerId);

        CUR_T       getBaseCurType  ()  const;
        CUR_T       getQuoteCurType ()  const;
        
    public:
        bool operator<  (const Order& aOther) const;
        bool operator== (const Order& aOther) const;

    private:
        ORDER_T     mOrderType;

        ldouble     mBase;
        CUR_T       mBaseCurT;

        ldouble     mQuote;
        CUR_T       mQuoteCurT;

        size_t      mOwnerId;

};

#endif
