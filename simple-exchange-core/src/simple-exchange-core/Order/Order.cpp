#include "simple-exchange-core/Order/Order.hpp"
#include "simple-exchange-core/Utils/CurrencyUtil.hpp"

Order::Order(ORDER_T aOrderT, CUR_T aBaseCurT, CUR_T aQuoteCurT, ldouble aBase, ldouble aQuote, size_t aOwnerId)
    : mOrderType(aOrderT),
    mBase(aBase),
    mBaseCurT(aBaseCurT),
    mQuote(aQuote),
    mQuoteCurT(aQuoteCurT),
    mOwnerId(aOwnerId)

{
}

Order::Order()
    : mOrderType(ORDER_T::NONE),
    mBase(0.0),
    mBaseCurT(CUR_T::NONE),
    mQuote(0.0),
    mQuoteCurT(CUR_T::NONE),
    mOwnerId(0)
{
}

void Order::setBase(ldouble aBase)
{
    mBase = CurrencyUtil::round2(aBase);
}

ldouble Order::getBase() const
{
    return mBase;
}

ldouble Order::getQuote() const
{
    return mQuote;
}

void Order::setQuote(ldouble aQuote)
{
    mQuote = aQuote;
}

void Order::setOwnerId(size_t aOwnerId)
{
    mOwnerId = aOwnerId;
}

size_t Order::getOwnerId() const
{
    return mOwnerId;
}

CUR_T Order::getBaseCurType() const
{
    return mBaseCurT;
}

CUR_T Order::getQuoteCurType() const
{
    return mQuoteCurT;
}

bool Order::operator<(const Order &aOther) const
{
    if (mOrderType == ORDER_T::BUY)
    {
        return mQuote < aOther.mQuote;
    }
    return mQuote > aOther.mQuote;
}

bool Order::operator==(const Order &aOther) const
{
    return (    getBase()           == aOther.getBase()         &&
                getQuote()          == aOther.getQuote()        &&
                getBaseCurType()    == aOther.getBaseCurType()  &&
                getQuoteCurType()   == aOther.getQuoteCurType() &&
                getOwnerId()        == aOther.getOwnerId()      &&
                getOrderType()      == aOther.getOrderType()    
    );
}

ORDER_T Order::getOrderType() const
{
    return mOrderType;
}

void Order::setOrderType(ORDER_T aOrderT)
{
    mOrderType = aOrderT;
}