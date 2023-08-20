#include <iostream>
#include <vector>
#include <thread>
#include <asio.hpp>
#include "EchoServer.h"

int main() {
    try {
        asio::io_context io_context;
        EchoServer s(io_context, 7);  // TCP Echo Service typically runs on port 7

        std::vector<std::thread> threads;
        for (std::size_t i = 0; i < 5; ++i) {
            threads.emplace_back([&io_context](){ io_context.run(); });
        }
        for (auto& th : threads) th.join();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}