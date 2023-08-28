#include <iostream>
#include "PrimeCheckerSession.h"
#include "JSONHandler.h"
#include "Logger.h"

PrimeCheckerSession::PrimeCheckerSession(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {}

void PrimeCheckerSession::start()
{
    read_request();
}

void PrimeCheckerSession::read_request()
{
    std::shared_ptr<PrimeCheckerSession> self(shared_from_this());
    socket_.async_read_some
    (
        boost::asio::buffer(data_, max_length),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                line_buffer += std::string(data_, length);

                // Extract lines (requests) from the buffer
                size_t pos;
                while ((pos = line_buffer.find('\n')) != std::string::npos)
                {
                    std::string line = line_buffer.substr(0, pos);
                    line_buffer = line_buffer.substr(pos + 1); // Remainder after the '\n'

                    if (loggingEnabled)
                    {
                        std::cout << "Received request: " << line << std::endl;
                    }

                    nlohmann::json_abi_v3_11_2::basic_json<> response_json = JSONHandler::handle_request(line);
                    std::string response;
                    
                    if (response_json.empty())
                    {
                        response = "{\"error\":\"malformed request\"}\n";
                    } 
                    else
                    {
                        response = response_json.dump() + "\n";
                    }

                    if (loggingEnabled) {
                        std::cout << "Sending response: " << response << std::endl;
                    }

                    // Synchronously write the response (for simplicity)
                    boost::asio::write(socket_, boost::asio::buffer(response));
                }

            read_request();
            }
        }
    );
}

void PrimeCheckerSession::write_response(const std::string& response)
{
    std::shared_ptr<PrimeCheckerSession> self(shared_from_this());
    boost::asio::async_write
    (
        socket_,
        boost::asio::buffer(response.c_str(), response.length()),
        [this, self](std::error_code ec, std::size_t)
        {
            if (!ec)
            {
                read_request();
            }
            else
            {
                socket_.close();
            }
        }
    );
}