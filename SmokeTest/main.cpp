#include <iostream>
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include "EchoService.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <port>\n";
            return 1;
        }

        int port = std::stoi(argv[1]);

        boost::asio::io_context io_context;
        EchoService s(io_context, port);  // TCP Echo Service typically runs on port 7

        std::vector<std::thread> threads;
        for (std::size_t i = 0; i < 5; ++i)
        {
            threads.emplace_back([&io_context](){ io_context.run(); });
        }
        for (std::thread& th : threads) th.join();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}