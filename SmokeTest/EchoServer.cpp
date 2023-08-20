#include "EchoServer.h"

EchoServer::EchoServer(asio::io_context& io_context, short port)
    : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    do_accept();
}

void EchoServer::do_accept() {
    acceptor_.async_accept(
        [this](std::error_code ec, asio::ip::tcp::socket socket) {
            if (!ec) {
                std::make_shared<EchoSession>(std::move(socket))->start();
            }
            do_accept();
        });
}