#include "Client.hpp"
#include <iostream>
#include "nlohmann/json.hpp"
#include "common.hpp"

Client::Client(boost::asio::io_service& io_service, tcp::resolver::iterator& it)
    : mId("0"),
    mName("NONE"),
    socket_(io_service)
{
    socket_.connect(*it);
    mId = ProcessRegistration();
}

void Client::SendMessage(
    const std::string &aRequestType, 
    const std::string &aMessage)
{
    nlohmann::json req;
    req["UserId"] = mId;
    req["ReqType"] = aRequestType;
    req["Message"] = aMessage;

    std::string request = req.dump();
    boost::asio::write(socket_, boost::asio::buffer(request, request.size()));
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
    std::cout << "Hello! Enter your name: ";
    std::cin >> mName;

    // Для регистрации Id не нужен, заполним его нулём
    SendMessage(Requests::Registration, mName);
    return ReadMessage();
}
