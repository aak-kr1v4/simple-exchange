#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session
{
    public:
        Session(boost::asio::io_service& io_service);

    public:
        tcp::socket& socket();

        void start();

        // Обработка полученного сообщения.
        void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

        void handle_write(const boost::system::error_code& error);

    private:
        tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];
};

#endif