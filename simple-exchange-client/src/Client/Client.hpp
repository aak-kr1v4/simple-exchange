#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

class Client
{
    public:
        Client(boost::asio::io_service& io_service, tcp::resolver::iterator& it);

    public:
        void SendMessage(const std::string& aRequestBody);
        std::string ReadMessage();
        
        std::string ProcessRegistration(); 

    private:
        tcp::socket socket_;

};

#endif