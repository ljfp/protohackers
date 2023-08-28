#pragma once

#include <boost/asio.hpp>
#include "PrimeCheckerSession.h"

class PrimeCheckerServer
{
public:
    PrimeCheckerServer(boost::asio::io_context& io_context, short port);

private:
    void do_accept();
    boost::asio::ip::tcp::acceptor acceptor_;
};
