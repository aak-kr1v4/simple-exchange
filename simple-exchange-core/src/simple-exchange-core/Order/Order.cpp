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

size_t Order::getOwnerId() const
{
    return mOwnerId;
}

bool Order::operator<(const Order& aOther) const
{
    if (mOrderType == ORDER_T::BUY)
    {
        return mQuote < aOther.mQuote;
    }
    return mQuote > aOther.mQuote;
}
