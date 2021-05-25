#include "Utils.hpp"


void primeFactors(int n, int* coll_arr)
{
    // Print the number of 2s that divide n
    while (n % 2 == 0)
    {
        coll_arr[0] = 2;
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
            if (coll_arr[0] == 0) {
                coll_arr[0] = i;
            }
            else {
                coll_arr[1] = i;
            }
            n = n / i;
        }
    }

    if (n > 2)
        coll_arr[1] = n;


}