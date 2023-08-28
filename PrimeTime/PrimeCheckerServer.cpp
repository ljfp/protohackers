#include "PrimeCheckerServer.h"

PrimeCheckerServer::PrimeCheckerServer(boost::asio::io_context& io_context, short port) : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    do_accept();
}

void PrimeCheckerServer::do_accept()
{
    acceptor_.async_accept
    (
        [this](std::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<PrimeCheckerSession>(std::move(socket))->start();
            }
            do_accept();
        }
    );
}
