// CH3101.cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#define uint unsigned int
using namespace std;
const int MX_N = 5e6 + 100;
bool isPrime[MX_N];
uint n, cs[MX_N];
vector<uint> primes;
int main()
{
    scanf("%u", &n);
    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = false;
    for (int i = 2; i <= n; i++)
        if (isPrime[i])
        {
            primes.push_back(i);
            for (int factor = 2; factor * i <= n; factor++)
                isPrime[i * factor] = false;
        }
    int siz = primes.size();
    for (int i = 0; i < siz; i++)
    {
        uint c = 0;
        for (int num = n; num; num /= primes[i])
            c += num / primes[i];
        printf("%u %u\n", primes[i], c);
    }
    return 0;
}