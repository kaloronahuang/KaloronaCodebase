// P1865.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1000000;
int sum[maxn], n, l, r, m;
bool isPrime[maxn];
void preprocessing()
{
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[1] = 0;
    isPrime[2] = 1;
    for (int i = 2; i < maxn; i++)
        if (isPrime[i])
            for (int j = 2; i * j < maxn; j++)
                isPrime[i * j] = 0;
    for (int i = 1; i < maxn; i++)
        sum[i] = sum[i - 1] + isPrime[i];
}
int main()
{
    preprocessing();
    scanf("%d%d", &n, &m);
    while (n--)
    {
        scanf("%d%d", &l, &r);
        if (l >= 1 && r <= m)
            printf("%d\n", sum[r] - sum[l - 1]);
        else
            printf("Crossing the line\n");
    }
    return 0;
}