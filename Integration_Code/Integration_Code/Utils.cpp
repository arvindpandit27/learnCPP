#include "Utils.hpp"


int * primeFactors(int n)
{
    int collect[2] = {};
    // Print the number of 2s that divide n
    while (n % 2 == 0)
    {
        collect[0] = 2;
        n = n / 2;
    }

    // n must be odd at this point. So we can skip
    // one element (Note i = i +2)
    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        // While i divides n, print i and divide n
        while (n % i == 0)
        {
           //cout << i << " ";
            if (collect[0] == 0) {
                collect[0] = i;
            }
            else {
                collect[1] = i;
            }
            n = n / i;
        }
    }

    if (n > 2)
        collect[1] = n;
       //cout << n << " ";

    return collect;
}