#ifndef CORE_HPP
#define CORE_HPP

#include "simple-exchange-core/User/User.hpp"
#include "simple-exchange-core/Order/Order.hpp"
#include <nlohmann/json.hpp>

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

    private:
        Core() = default;

    private:
        users_map_t mUsers;
        p_queue_t   mbuyOrders;
        p_queue_t   mSellOrders;
};

#endif