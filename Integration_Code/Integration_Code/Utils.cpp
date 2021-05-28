#include "Utils.hpp"
#include <algorithm>


int board_rows[5] = { 2,3,5,7,11 };
int board_cols[5] = { 13,17,19,23,29 };

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

void findXYinBoard(int prime1, int prime2) {
    int i = 0;
    while (i < 5)
    {
        if (board_rows[i] == prime1) {
            break;
        }
        i++;
    }

    //indices[0] = i;

    int j = 0;
    while (j < 5)
    {
        if (board_cols[j] == prime2) {
            break;
        }
        j++;
    }

    //indices[1] = j;
}