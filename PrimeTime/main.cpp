#include <iostream>
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include "PrimeCheckerServer.h"
#include "Logger.h"

bool loggingEnabled = false;

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2 || argc > 3)
        {
        std::cerr << "Usage: " << argv[0] << " <port> [--verbose]\n";
        return 1;
        }

        int port = std::stoi(argv[1]);

        if (argc == 3 && std::string(argv[2]) == "--verbose")
        {
            loggingEnabled = true;
        }

        boost::asio::io_context io_context;
        PrimeCheckerServer s(io_context, port);
        std::vector<std::thread> threads;
        for (std::size_t i = 0; i < 5; ++i)
        {
            threads.emplace_back([&io_context](){ io_context.run(); });
        }
        for (std::thread& th : threads) th.join();
        //io_context.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}