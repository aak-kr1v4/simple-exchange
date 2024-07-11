#include "simple-exchange-core/User/User.hpp"
#include "gtest/gtest.h"

TEST(UserTest, DefaultConstructor) 
{

    User user;
    EXPECT_EQ(user.getName(), "NONE");
    EXPECT_EQ(user.getId(), 0);
    EXPECT_NEAR(user.getBalance(cur_t::NONE), 0.0, 0.001);
}

TEST(UserTest, ParameterizedConstructorName) 
{

    User user("User Name");
    EXPECT_EQ(user.getName(), "User Name");
    EXPECT_EQ(user.getId(), 0);
}

TEST(UserTest, ParametrizedConstructorNameId) 
{

    User user("User Name", 159);
    EXPECT_EQ(user.getName(), "User Name");
    EXPECT_EQ(user.getId(), 159);
}

TEST(UserTest, SetName) 
{

    User user;
    user.setName("User Name");
    EXPECT_EQ(user.getName(), "User Name");
}

TEST(UserTest, SetId) 
{

    User user;
    user.setId(159);
    EXPECT_EQ(user.getId(), 159);
}

TEST(UserTest, SetGetBalance) 
{

    User user;
    user.setBalance(CURRENCY_TYPE::USD, 100.21);
    EXPECT_NEAR(user.getBalance(CURRENCY_TYPE::USD), 100.21, 0.001);

    user.setBalance(CURRENCY_TYPE::RUB, 0.817);
    EXPECT_NEAR(user.getBalance(CURRENCY_TYPE::RUB), 0.82, 0.001);

    EXPECT_NEAR(user.getBalance(CURRENCY_TYPE::NONE), 0.0, 0.001);
}