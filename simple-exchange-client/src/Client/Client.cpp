#include "Client.hpp"
#include <iostream>
#include "nlohmann/json.hpp"
#include "common.hpp"

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator& it)
    : socket_(io_service)
{
    socket_.connect(*it);
}

void Client::SendMessage(const std::string& aRequestBody)
{
    boost::asio::write(socket_, boost::asio::buffer(aRequestBody, aRequestBody.size()));
}

std::string Client::ReadMessage()
{
    boost::asio::streambuf b;
    boost::asio::read_until(socket_, b, "\0");
    std::istream is(&b);
    std::string line(std::istreambuf_iterator<char>(is), {});
    return line;
}

std::string Client::ProcessRegistration()
{
    std::string name;
    std::cout << "Hello! Enter your name: ";
    std::cin >> name;

    nlohmann::json request = 
    {
        {"UserId", "0"},
        {"ReqT", REQ_T::REGISTRATION},
        {"Message", name}
    };

    SendMessage(request.dump());
    return ReadMessage();
}
