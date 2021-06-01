#include "Utils.hpp"
#include <algorithm>


int board_rows[5] = { 13,17,19,23,29 };
int board_cols[5] = { 2,3,5,7,11 };

void primeFactors(int n, int* coll_arr){

    // Input : An array to store the prime factors, the number to be factorsised
    // Output : Prime factors
    // Purpose : A function to get a unique combination of prime factors to extract row and column position

    while (n % 2 == 0)
    {
        coll_arr[0] = 2;
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        while (n % i == 0)
        {
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

void findXYinBoard(int prime2, int prime1, int *indices) {

    // Input : An array to store the row and column number, Prime factors
    // Output : Get Row and Column value
    // Purpose : Interfaces with a cell represented by a unique prime number and board graphics
    int i = 0;
    while (i < 5)
    {
        if (board_rows[i] == prime1) {
            break;
        }
        i++;
    }

    indices[0] = i;

    int j = 0;
    while (j < 5)
    {
        if (board_cols[j] == prime2) {
            break;
        }
        j++;
    }

    indices[1] = j;
}