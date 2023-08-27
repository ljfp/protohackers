#pragma once

#include <boost/asio.hpp>
#include "EchoSession.h"

class EchoService 
{
public:
    EchoService(boost::asio::io_context& io_context, short port);

private:
    void do_accept();
    boost::asio::ip::tcp::acceptor acceptor_;
};