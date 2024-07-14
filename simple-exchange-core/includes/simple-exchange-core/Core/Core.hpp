#ifndef CORE_HPP
#define CORE_HPP

#include "simple-exchange-core/User/User.hpp"
#include "simple-exchange-core/Order/Order.hpp"
#include <nlohmann/json.hpp>
#include "simple-exchange-core/Deal/Deal.hpp"

class Core
{
    public:
        Core(const Core&) = delete;
        Core& operator=(const Core&) = delete;

    public:
        static Core& GetCore();

        // "Регистрирует" нового пользователя и возвращает его ID.
        std::string RegisterNewUser(const std::string& aUserName);

        // Запрос имени клиента по ID
        std::string GetUserName(size_t aUserId);

        // Запрос на создание заявки
        std::string CreateOrder(const nlohmann::json& aOrderData, size_t aUserId);

        // Запрос на показ баланса
        std::string GetUserBalance(size_t aUserId);

        void  matchOrders();

        pq_orders_t findBestCandidatesToMatch(const Order& aOrderToMatch);
        void  removeOrderFromPq(const Order& aOrderToRemove, pq_orders_t& aPqWhereDelete);

        void setUserBalance(size_t aUserId, CUR_T aCurT, ldouble aValue);
        void updateUserBalances(const Order& aBuyOrder, const Order& aSellOrder, 
                                ldouble aDealBase, ldouble aDealBaseInQuoteCurT);

        void createDeal(const Order& aBuyOrder, const Order& aSellOrder, 
                        ldouble aDealBase, ldouble aDealBaseInQuoteCurT);
        void setUsersMap(const users_map_t& aUsersMap);
        void setBuyOrdersMap(const pq_orders_t& aBuyOrders);
        void setSellOrdersMap(const pq_orders_t& aSellOrders);
        std::vector<Deal> getDeals() const;
        users_map_t getUsers() const;

        pq_orders_t getBuyOrders()  const;
        pq_orders_t getSellOrders() const;
        void clear();

    private:
        Core() = default;

    private:
        users_map_t   mUsers;
        pq_orders_t   mbuyOrders;
        pq_orders_t   mSellOrders;
        std::vector<Deal> mDeals;
};

#endif