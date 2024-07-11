#include "Client/Client.hpp"
#include "common.hpp"
#include <iostream>
#include "nlohmann/json.hpp"
#include "simple-exchange-core/User/User.hpp"
#include "simple-exchange-core/Order/Order.hpp"
#include "ProcessMenu/ProcessMenu.hpp"

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
                         "2) Add Order\n"
                         "3) Exit\n"
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
                        {"ReqT", REQ_T::HELLO},
                        {"Message", ""}
                    };

                    client.SendMessage(request.dump());
                    std::cout << client.ReadMessage();
                    break;
                }
                case 2:
                {
                    nlohmann::json request;
                    if (ProcessMenu::inputOrderCreate(request)) 
                    {
                        request["UserId"] = registeredUser.getId();
                        request["ReqT"] = REQ_T::ORDER_CREATE;

                        client.SendMessage(request.dump());
                        std::cout << client.ReadMessage();
                    } 
                    else 
                    {
                        std::cout << "Order creation failed.\n";
                    }

                    break;
                }
                case 3:
                {
                    exit(0);
                    break;
                }
                default:
                {
                    std::cout << "Unknown menu option\n" << std::endl;
                    break;
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