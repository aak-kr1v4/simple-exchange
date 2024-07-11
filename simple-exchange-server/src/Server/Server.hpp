#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Session/Session.hpp"

class Server
{
    public:
        Server(boost::asio::io_service& io_service);

    public:
        void handle_accept(Session* new_session, const boost::system::error_code& error);

    private:
        boost::asio::io_service& io_service_;
        tcp::acceptor acceptor_;
};

#endif