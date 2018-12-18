// POJ2689.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#define uint unsigned int
using namespace std;
const int LIT = 1000006, INF = 0x7fffffff;
uint L, R;
bool isPrime[LIT], v[LIT];
vector<uint> primes, ans;
int main()
{
    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = false;
    for (int i = 2; i < LIT; i++)
        if (isPrime[i])
        {
            primes.push_back(i);
            for (int tim = 2; tim * i < LIT; tim++)
                isPrime[tim * i] = false;
        }
    while (scanf("%u%u", &L, &R) != EOF)
    {
        memset(v, true, sizeof(v));
        if (L == 1)
            v[0] = false;
        ans.clear();
        uint siz = primes.size();
        for (int pcur = 0; pcur < siz; pcur++)
            for (int factor = ((L - 1) / primes[pcur]) + 1; factor <= (R / primes[pcur]); factor++)
                if (factor > 1)
                    v[(primes[pcur] * factor) - L] = false;
        for (int num = L; num <= R; num++)
            if (v[num - L])
                ans.push_back(num);
        uint x1 = 0, x2 = INF, y1 = 0, y2 = 0;
        siz = ans.size();
        for (int i = 0; i < siz - 1; i++)
        {
            if (x2 - x1 > ans[i + 1] - ans[i])
                x1 = ans[i], x2 = ans[i + 1];
            if (y2 - y1 < ans[i + 1] - ans[i])
                y1 = ans[i], y2 = ans[i + 1];
        }
        if (x1)
            printf("%u,%u are closest, %u,%u are most distant.\n", x1, x2, y1, y2);
        else
            printf("There are no adjacent primes.\n");
    }
    return 0;
}