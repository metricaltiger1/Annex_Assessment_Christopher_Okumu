// Question 1: Find the p-th Factor (C)
// Problem Statement
// Given two integers, n and p, find the p-th smallest factor of n.

// A factor of n is any positive integer that divides n with no remainder.

// Requirements
// Find all positive factors of n
// Sort them in ascending order
// Return the p-th smallest factor (using 1-based indexing)
// If n has fewer than p factors, return 0
// Constraints
// 1 ≤ n ≤ 10¹⁵
// 1 ≤ p ≤ 10⁹
// Example
// Input: n = 10, p = 3
// Output: 5

// Explanation:
// Factors of 10: {1, 2, 5, 10}
// The 3rd factor is 5.

// Function Signature
// long pthFactor(long n, long p) {
//     // Your code here
// }

#include <stdio.h>
#include <math.h>

long pthFactor(long n, long p)
{
    long count = 0;

    // 1st pass: countting small factors in order
    for (long i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            count++;

            if (count == p)
            {
                return i;
            }
        }
    }

    // 2nd pass: handle larger factors in correct order
    for (long i = (long)sqrt(n); i >= 1; i--)
    {
        if (n % i == 0)
        {
            if (i * i == n)
            {
                continue;
            }

            long largeFactor = n / i;
            count++;

            if (count == p)
            {
                return largeFactor;
            }
        }
    }

    return 0;
}

int main()
{
    long result = pthFactor(10, 3);
    printf("%ld\n", result);
    return 0;
}