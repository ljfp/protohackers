#pragma once

#include <nlohmann/json.hpp>

class JSONHandler
{
public:
    static nlohmann::json handle_request(const std::string& request);
};
