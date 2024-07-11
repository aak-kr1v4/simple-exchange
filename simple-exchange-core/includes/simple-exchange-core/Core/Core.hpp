#ifndef CORE_HPP
#define CORE_HPP

#include <string>
#include <map>
#include <cstdlib>

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
        std::string GetUserName(const std::string& aUserId);

    private:
        Core() = default;

    private:
        std::map<size_t, std::string> mUsers; 
};

#endif