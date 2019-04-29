#include "Prime.h"
#include <iostream>
using namespace std;

void buildPrime(int n) {
    prime.push_back(2);
    for (int i = 3; i <= n; i += 2)
    {
        bool isprime = true;
        for (int j = 0; isprime && j < prime.size() && prime[j] <= sqrt(i); j++)
        {
            if (i % prime[j] == 0) isprime = false;
        }
        if (isprime) prime.push_back(i);
    }
}

int findPrimeMoreThan(double d) {
    for (auto i : prime)
        if(i > d) return i;

    return  -1;
}