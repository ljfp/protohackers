#pragma once
#include <boost/asio.hpp>

class PrimeCheckerSession : public std::enable_shared_from_this<PrimeCheckerSession>
{
public:
    explicit PrimeCheckerSession(boost::asio::ip::tcp::socket socket);
    void start();

private:
    void read_request();
    void write_response(const std::string& response);
    boost::asio::ip::tcp::socket socket_;
    enum { max_length = 4096 };
    char data_[max_length];
    std::string line_buffer;
};
