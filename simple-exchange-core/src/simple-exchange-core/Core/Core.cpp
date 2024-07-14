#include "simple-exchange-core/Core/Core.hpp"
#include "simple-exchange-core/User/User.hpp"
#include "simple-exchange-core/Utils/CurrencyUtil.hpp"
#include "nlohmann/json.hpp"
#include <iostream>

Core& Core::GetCore()
{
    static Core instance;
    return instance;
}

std::string Core::RegisterNewUser(const std::string& aUserName)
{
    size_t newUserId = mUsers.size();
    User newUser(aUserName, newUserId);

    mUsers[newUserId] = newUser;

    nlohmann::json response = 
    {
        {"UserName", aUserName},
        {"UserId",   newUserId}
    };

    return response.dump();
}

std::string Core::GetUserName(size_t aUserId)
{
    const auto userIt = mUsers.find(aUserId);

    if (userIt == mUsers.cend())
    {
        return "Error! Unknown User";
    }
    else
    {
        return userIt->second.getName();
    }
}

std::string Core::CreateOrder(const nlohmann::json& aOrderData, size_t aUserId)
{
    Order newOrder(
            aOrderData["OrderT"],
            aOrderData["BaseCurT"],
            aOrderData["QuoteCurT"],
            aOrderData["BaseValue"],
            aOrderData["QuoteValue"],
            aUserId
    );

    if (newOrder.getOrderType() == ORDER_T::BUY)
    {
        mbuyOrders.push(newOrder);
    }
    else
    {
        mSellOrders.push(newOrder);
    }

    matchOrders();
    return "Order succesfully created!\n";
}

void Core::setUserBalance(size_t aUserId, CUR_T aCurT, ldouble aAmount)
{
    mUsers[aUserId].setBalance(aCurT, aAmount);
}

void Core::matchOrders()
{
    while (!mbuyOrders.empty() && !mSellOrders.empty())
    {
        Order buyOrder  = mbuyOrders.top();
        CUR_T buyOrderBaseCurT  = buyOrder.getBaseCurType();
        CUR_T buyOrderQuoteCurT = buyOrder.getQuoteCurType();

        pq_orders_t candidates = findBestCandidatesToMatch(buyOrder);

        if (candidates.empty()) return;

        while(!candidates.empty())
        {
            Order curCandidate = candidates.top();
            CUR_T curCandidateBaseCurT  = curCandidate.getBaseCurType();
            CUR_T curCandidateQuoteCurT = curCandidate.getQuoteCurType();

            if (buyOrder.getQuote() >= curCandidate.getQuote())
            {
                
                if (buyOrder.getBase() < curCandidate.getBase())
                {
                    ldouble dealBase = buyOrder.getBase(); // Стоимость сделки
                    ldouble dealBaseInQuoteCur = dealBase * buyOrder.getQuote(); // Стоимость сделки в валюте котировки

                    mbuyOrders.pop(); // Сделка полностью выполнена 

                    // Частично выполним сделку на продажу
                    ldouble curCandidateNewBase = curCandidate.getBase() - dealBase;

                    // Обновляем данные о сделке на продажу
                    removeOrderFromPq(curCandidate, mSellOrders);
                    candidates.pop();

                    curCandidate.setBase(curCandidateNewBase);

                    mSellOrders.push(curCandidate);
                    candidates.push(curCandidate);

                    updateUserBalances(buyOrder, curCandidate, dealBase, dealBaseInQuoteCur);

                    createDeal(buyOrder, curCandidate, dealBase, dealBaseInQuoteCur);
                    break;

                }
                else if (buyOrder.getBase() > curCandidate.getBase())
                {
                    ldouble dealBase = curCandidate.getBase();
                    ldouble dealBaseInQuoteCur = dealBase * buyOrder.getQuote();

                    removeOrderFromPq(curCandidate, mSellOrders); // Сделка полностью выполнена
                    candidates.pop();

                    // Частично выполним сделку на покупку
                    ldouble buyOrderNewBase = buyOrder.getBase() - dealBase;

                    // Обновляем данные о сделке на покупку
                    mbuyOrders.pop();
                    buyOrder.setBase(buyOrderNewBase);
                    mbuyOrders.push(buyOrder);

                    updateUserBalances(buyOrder, curCandidate, dealBase, dealBaseInQuoteCur);
                    createDeal(buyOrder, curCandidate, dealBase, dealBaseInQuoteCur);

                    break;

                }
                else
                {
                    ldouble dealBase = buyOrder.getBase(); 
                    ldouble dealBaseInQuoteCur = dealBase * buyOrder.getQuote();

                    // Выполняем обе сделки
                    mbuyOrders.pop(); 
                    candidates.pop();
                    removeOrderFromPq(curCandidate, mSellOrders);  

                    updateUserBalances(buyOrder, curCandidate, dealBase, dealBaseInQuoteCur);
                    createDeal(buyOrder, curCandidate, dealBase, dealBaseInQuoteCur);
                    break;
                }
            }
            else
            {
                return;
            }
        }
    }
}

pq_orders_t Core::findBestCandidatesToMatch(const Order& aOrderToMatch)
{
    pq_orders_t pqWhereFind;
    pq_orders_t candidates;

    if (aOrderToMatch.getOrderType() == ORDER_T::BUY)
    {
        pqWhereFind = mSellOrders;
    }
    else
    {
        pqWhereFind = mbuyOrders;
    }

    while (!pqWhereFind.empty())
    {
        Order candidate = pqWhereFind.top();
        if (candidate.getOwnerId() != aOrderToMatch.getOwnerId() && 
            aOrderToMatch.getBaseCurType() == candidate.getBaseCurType() &&
            aOrderToMatch.getQuoteCurType() == candidate.getQuoteCurType()
            )
        {
            candidates.push(candidate);
        }
        pqWhereFind.pop();
    }

    return candidates;
}

void Core::removeOrderFromPq(const Order &aOrderToRemove, pq_orders_t& aPqWhereDelete)
{
    std::vector<Order> temp;

    while (!aPqWhereDelete.empty()) 
    {
        if (!(aPqWhereDelete.top() == aOrderToRemove)) 
        {
            temp.push_back(aPqWhereDelete.top());
        }
        aPqWhereDelete.pop();
    }

    for (const auto& item : temp) 
    {
        aPqWhereDelete.push(item);
    }
}

void Core::updateUserBalances(const Order& aBuyOrder, const Order& aSellOrder, 
                              ldouble aDealBase, ldouble aDealBaseInQuoteCur)
{
    size_t buyerId = aBuyOrder.getOwnerId();
    size_t sellerId = aSellOrder.getOwnerId();

    ldouble buyerBalanceBase   = mUsers[buyerId].getBalance(aBuyOrder.getBaseCurType());
    ldouble buyerBalanceQuote  = mUsers[buyerId].getBalance(aBuyOrder.getQuoteCurType());

    ldouble sellerBalanceBase  = mUsers[sellerId].getBalance(aSellOrder.getBaseCurType());
    ldouble sellerBalanceQuote = mUsers[sellerId].getBalance(aSellOrder.getQuoteCurType());

    buyerBalanceBase  += aDealBase;
    buyerBalanceQuote -= aDealBaseInQuoteCur;

    sellerBalanceBase -= aDealBase;
    sellerBalanceQuote += aDealBaseInQuoteCur;

    setUserBalance(buyerId, aBuyOrder.getBaseCurType(), buyerBalanceBase);
    setUserBalance(buyerId, aBuyOrder.getQuoteCurType(), buyerBalanceQuote);

    setUserBalance(sellerId, aSellOrder.getBaseCurType(), sellerBalanceBase);
    setUserBalance(sellerId, aSellOrder.getQuoteCurType(), sellerBalanceQuote);

}

void Core::createDeal(const Order &aBuyOrder, const Order &aSellOrder, ldouble aDealBase, ldouble aDealBaseInQuoteCurT)
{
    Deal deal;

    deal.baseCurT = aBuyOrder.getBaseCurType();
    deal.quoteCurT = aSellOrder.getQuoteCurType();
    deal.buyerId = aBuyOrder.getOwnerId();
    deal.sellerId = aSellOrder.getOwnerId();
    deal.dealBase = aDealBase;
    deal.dealBaseInQuoteCurT = aDealBaseInQuoteCurT;

    mDeals.push_back(deal);
}

void Core::setUsersMap(const users_map_t &aUsersMap)
{
    mUsers = aUsersMap;
}

void Core::setBuyOrdersMap(const pq_orders_t &aBuyOrders)
{
    mbuyOrders = aBuyOrders;
}

void Core::setSellOrdersMap(const pq_orders_t &aSellOrders)
{
    mSellOrders = aSellOrders;
}

std::vector<Deal> Core::getDeals() const
{
    return mDeals;
}

users_map_t Core::getUsers() const
{
    return mUsers;
}

pq_orders_t Core::getBuyOrders() const
{
    return mbuyOrders;
}

pq_orders_t Core::getSellOrders() const
{
    return mSellOrders;
}

void Core::clear()
{
    mbuyOrders = {};
    mSellOrders = {};
    mUsers = {};
    mDeals = {};
}

std::string Core::GetUserBalance(size_t aUserId)
{
    std::ostringstream oss;
    for (ushort i = 1; i < static_cast<ushort>(CUR_T::END_OF_ENUM); ++i) 
    {
        CUR_T curT = static_cast<CUR_T>(i);

        oss << CurrencyUtil::getCurCodeStr(curT) << ": " 
            << mUsers[aUserId].getBalance(curT) << "\n";
    }

    return oss.str();
}
