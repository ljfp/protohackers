#include <cmath>
#include "PrimeChecker.h"

bool PrimeChecker::is_prime(int64_t number) 
{
    if (number <= 1) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;

    /*
    This is an old trick. 
    You can divide the factors of an integer in two groups:
    small factors and large factors.
    The smaller factor is less than, or is at most equal to, the square root.
    The larger factors are greater than the square root.
    If no factor less than or equal to the square root is found, 
    it follows that the number under investigation is prime.
    */
    for (int64_t i = 3; i <= std::sqrt(number); i += 2) 
    {
        if (number % i == 0) return false;
    }
    return true;
}
