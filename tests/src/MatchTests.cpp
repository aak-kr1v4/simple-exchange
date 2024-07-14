#include "simple-exchange-core/Core/Core.hpp"
#include "gtest/gtest.h"

TEST(MatchTests, TwoBuyOrders) 
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order buyOrder2(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 2);

    pq_orders_t buyOrders;
    buyOrders.push(buyOrder1);
    buyOrders.push(buyOrder2);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();


    EXPECT_EQ(deals.size(), 0);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), 0);

    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 2);

}

TEST(MatchTests, TwoSellOrders) 
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};

    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order sellOrder2(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 10, 62, 2);

    pq_orders_t sellOrders;
    sellOrders.push(sellOrder1);
    sellOrders.push(sellOrder2);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();


    EXPECT_EQ(deals.size(), 0);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), 0);

    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 2);
}

TEST(MatchTests, OneBuyOneSellOrdersEqBaseEqPrice)
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 10, 62, 2);

    pq_orders_t buyOrders;
    pq_orders_t sellOrders;

    buyOrders.push(buyOrder1);
    sellOrders.push(sellOrder1);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();

    EXPECT_EQ(deals.size(), 1);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 10);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), -620);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), -10);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), 620);

    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 0);
    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 0);

}

TEST(MatchTests, OneBuyOneSellOrdersFromOneUser)
{
    Core::GetCore().clear();
    User  user1{"user1", 1};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 10, 62, 1);

    pq_orders_t buyOrders;
    pq_orders_t sellOrders;

    buyOrders.push(buyOrder1);
    sellOrders.push(sellOrder1);

    users_map_t users;

    users[1] = user1;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();

    EXPECT_EQ(deals.size(), 0);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), 0);

    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 1);
    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 1);
}

TEST(MatchTests, OneBuyOneSellWithoutDeal)
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 10, 63, 2);

    pq_orders_t buyOrders;
    pq_orders_t sellOrders;

    buyOrders.push(buyOrder1);
    sellOrders.push(sellOrder1);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();

    EXPECT_EQ(deals.size(), 0);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), 0);

    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 1);
    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 1);
}

TEST(MatchTests, PriorityBuyOrders)
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};
    User  user3{"user3", 3};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order buyOrder2(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 20, 63, 2);
    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 20, 61, 3);

    pq_orders_t buyOrders;
    pq_orders_t sellOrders;

    buyOrders.push(buyOrder1);
    buyOrders.push(buyOrder2);
    sellOrders.push(sellOrder1);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;
    users[3] = user3;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();

    EXPECT_EQ(deals.size(), 1);
    EXPECT_EQ(deals[0].buyerId, 2);
    EXPECT_EQ(deals[0].sellerId, 3);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), 20);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), -1260);
    EXPECT_EQ(users[3].getBalance(CUR_T::USD), -20);
    EXPECT_EQ(users[3].getBalance(CUR_T::RUB), 1260);

    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 1);
    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 0);
}

TEST(MatchTests, PrioritySellOrders)
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};
    User  user3{"user3", 3};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 20, 63, 2);
    Order sellOrder2(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 10, 61, 3);

    pq_orders_t buyOrders;
    pq_orders_t sellOrders;

    buyOrders.push(buyOrder1);
    sellOrders.push(sellOrder1);
    sellOrders.push(sellOrder2);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;
    users[3] = user3;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();

    EXPECT_EQ(deals.size(), 1);
    EXPECT_EQ(deals[0].buyerId, 1);
    EXPECT_EQ(deals[0].sellerId, 3);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 10);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), -620);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), 0);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), 0);
    EXPECT_EQ(users[3].getBalance(CUR_T::USD), -10);
    EXPECT_EQ(users[3].getBalance(CUR_T::RUB), 620);

    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 0);
    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 1);   
}

TEST(MatchTests, PartialExecutionBuyOrder)
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};
    User  user3{"user3", 3};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 100, 62, 1);
    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 30, 60, 2);
    Order sellOrder2(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 40, 61, 3);

    pq_orders_t buyOrders;
    pq_orders_t sellOrders;

    buyOrders.push(buyOrder1);
    sellOrders.push(sellOrder1);
    sellOrders.push(sellOrder2);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;
    users[3] = user3;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();

    EXPECT_EQ(deals.size(), 2);
    EXPECT_EQ(deals[0].buyerId, 1);
    EXPECT_EQ(deals[0].sellerId, 2);
    EXPECT_EQ(deals[1].buyerId, 1);
    EXPECT_EQ(deals[1].sellerId, 3);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 70);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), -4340);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), -30);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), 1860);
    EXPECT_EQ(users[3].getBalance(CUR_T::USD), -40);
    EXPECT_EQ(users[3].getBalance(CUR_T::RUB), 2480);

    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 1);
    EXPECT_EQ(Core::GetCore().getBuyOrders().top().getBase(), 30);
    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 0);
}

TEST(MatchTests, PartialExecutionSellOrder)
{
    Core::GetCore().clear();
    User  user1{"user1", 1};
    User  user2{"user2", 2};
    User  user3{"user3", 3};

    Order buyOrder1(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 10, 62, 1);
    Order buyOrder2(ORDER_T::BUY, CUR_T::USD, CUR_T::RUB, 20, 63, 2);
    Order sellOrder1(ORDER_T::SELL, CUR_T::USD, CUR_T::RUB, 50, 61, 3);

    pq_orders_t buyOrders;
    pq_orders_t sellOrders;

    buyOrders.push(buyOrder1);
    buyOrders.push(buyOrder2);
    sellOrders.push(sellOrder1);

    users_map_t users;

    users[1] = user1;
    users[2] = user2;
    users[3] = user3;

    Core::GetCore().setUsersMap(users);
    Core::GetCore().setBuyOrdersMap(buyOrders);
    Core::GetCore().setSellOrdersMap(sellOrders);
    Core::GetCore().matchOrders();

    std::vector<Deal> deals = Core::GetCore().getDeals();
    users = Core::GetCore().getUsers();

    EXPECT_EQ(deals.size(), 2);
    EXPECT_EQ(deals[0].buyerId, 2);
    EXPECT_EQ(deals[0].sellerId, 3);
    EXPECT_EQ(deals[1].buyerId, 1);
    EXPECT_EQ(deals[1].sellerId, 3);

    EXPECT_EQ(users[1].getBalance(CUR_T::USD), 10);
    EXPECT_EQ(users[1].getBalance(CUR_T::RUB), -620);
    EXPECT_EQ(users[2].getBalance(CUR_T::USD), 20);
    EXPECT_EQ(users[2].getBalance(CUR_T::RUB), -1260);
    EXPECT_EQ(users[3].getBalance(CUR_T::USD), -30);
    EXPECT_EQ(users[3].getBalance(CUR_T::RUB), 1880);

    EXPECT_EQ(Core::GetCore().getSellOrders().size(), 1);
    EXPECT_EQ(Core::GetCore().getSellOrders().top().getBase(), 20);
    EXPECT_EQ(Core::GetCore().getBuyOrders().size(), 0);   
}