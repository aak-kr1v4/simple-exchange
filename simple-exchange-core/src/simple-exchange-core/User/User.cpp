#include "simple-exchange-core/User/User.hpp"
#include "simple-exchange-core/Utils/CurrencyUtil.hpp"

User::User()
    : mId(0),
    mName("NONE")
{
}

User::User(const std::string& aName)
    : mId(0),
    mName(aName)
{
}

User::User(const std::string &aName, size_t aId)
    : mId(aId),
    mName(aName)
{
}

std::string User::getName()
{
    return mName;
}

void User::setName(const std::string& aName)
{
    mName = aName;
}

size_t User::getId()
{
    return mId;
}

void User::setId(size_t aId)
{
    mId = aId;
}

void User::setBalance(CURRENCY_TYPE aCurType, ldouble aAmount)
{
    mBalances[aCurType] = CurrencyUtil::round2(aAmount);
}

ldouble User::getBalance(cur_t aCurType)
{
    const auto it = mBalances.find(aCurType);
    if (it != mBalances.end()) {
        return it->second;
    }
    return 0.0;
}