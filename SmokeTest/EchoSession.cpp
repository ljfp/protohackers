#include "EchoSession.h"

EchoSession::EchoSession(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {}

void EchoSession::start()
{
    do_read();
}

void EchoSession::do_read()
{
    std::shared_ptr<EchoSession> self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_write(length);
            }
        }
    );
}

void EchoSession::do_write(std::size_t length)
{
    std::shared_ptr<EchoSession> self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(data_, length),
        [this, self](std::error_code ec, std::size_t)
        {
            if (!ec)
            {
                do_read();
            }
        }
    );
}