#include "JSONHandler.h"
#include "PrimeChecker.h"

nlohmann::json JSONHandler::handle_request(const std::string& request)
{
    try
    {
        nlohmann::json j_request = nlohmann::json::parse(request);

        if (j_request["method"] == "isPrime" && j_request.contains("number"))
        {
            int64_t number = j_request["number"];
            bool prime = PrimeChecker::is_prime(number);
            return {{"method", "isPrime"}, {"prime", prime}};
        }
    }
    catch (...)
    {
        // Catch all exceptions, including parsing errors.
    }
    // For malformed requests, return an empty JSON to indicate an error.
    return {};
}
