#pragma once

#include <asio.hpp>

class EchoSession : public std::enable_shared_from_this<EchoSession> {
public:
    explicit EchoSession(asio::ip::tcp::socket socket);
    void start();

private:
    void do_read();
    void do_write(std::size_t length);

    asio::ip::tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};