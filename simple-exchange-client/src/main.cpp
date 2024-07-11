#include "Client/Client.hpp"
#include "common.hpp"
#include <iostream>
#include "nlohmann/json.hpp"
#include "simple-exchange-core/User/User.hpp"

int main()
{
    try
    {
        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(tcp::v4(), "127.0.0.1", std::to_string(port));
        tcp::resolver::iterator iterator = resolver.resolve(query);

        Client client(io_service, iterator);

        std::string registerRespone = client.ProcessRegistration();
        const auto j = nlohmann::json::parse(registerRespone);

        User registeredUser(j["UserName"], j["UserId"]);

        while (true)
        {
            // Тут реализовано "бесконечное" меню.
            std::cout << "Menu:\n"
                         "1) Hello Request\n"
                         "2) Exit\n"
                         << std::endl;

            short menu_option_num;
            std::cin >> menu_option_num;
            switch (menu_option_num)
            {
                case 1:
                {
                    nlohmann::json request = 
                    {
                        {"UserId", registeredUser.getId()},
                        {"ReqType", REQ_T::HELLO},
                        {"Message", ""}
                    };

                    client.SendMessage(request.dump());
                    std::cout << client.ReadMessage();
                    break;
                }
                case 2:
                {
                    exit(0);
                    break;
                }
                default:
                {
                    std::cout << "Unknown menu option\n" << std::endl;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}