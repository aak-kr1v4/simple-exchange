#ifndef CORE_HPP
#define CORE_HPP

#include "simple-exchange-core/User/User.hpp"

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

    private:
        Core() = default;

    private:
        users_map_t mUsers;
};

#endif