#include "simple-exchange-core/Core/Core.hpp"
#include "simple-exchange-core/User/User.hpp"
#include "nlohmann/json.hpp"

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
