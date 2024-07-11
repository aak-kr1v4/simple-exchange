#include "simple-exchange-core/Core/Core.hpp"

Core &Core::GetCore()
{
    static Core instance;
    return instance;
}

std::string Core::RegisterNewUser(const std::string &aUserName)
{
    size_t newUserId = mUsers.size();
    mUsers[newUserId] = aUserName;

    return std::to_string(newUserId);
}

std::string Core::GetUserName(const std::string &aUserId)
{
    const auto userIt = mUsers.find(std::stoi(aUserId));
    if (userIt == mUsers.cend())
    {
        return "Error! Unknown User";
    }
    else
    {
        return userIt->second;
    }
}
