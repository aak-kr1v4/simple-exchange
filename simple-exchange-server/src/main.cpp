#include <iostream>
#include "Server/Server.hpp"

using boost::asio::ip::tcp;


int main()
{
    try
    {
        boost::asio::io_service io_service;

        Server s(io_service);

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}