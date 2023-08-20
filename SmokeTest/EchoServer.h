#pragma once

#include <asio.hpp>
#include "EchoSession.h"

class EchoServer {
public:
    EchoServer(asio::io_context& io_context, short port);

private:
    void do_accept();
    asio::ip::tcp::acceptor acceptor_;
};