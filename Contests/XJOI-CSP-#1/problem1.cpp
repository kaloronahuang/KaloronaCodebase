// problem1.cpp
#include <bits/stdc++.h>

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

using namespace std;

int fac[MAX_N], n;

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void print(int id, int ans)
{
    int ldigit = id % 10;
    if (id % 100 <= 20 && id % 100 >= 11)
        printf("The %dth answer is ", id);
    else if (ldigit == 1)
        printf("The %dst answer is ", id);
    else if (ldigit == 2)
        printf("The %dnd answer is ", id);
    else if (ldigit == 3)
        printf("The %drd answer is ", id);
    else
        printf("The %dth answer is ", id);
    printf("%d.", ans);
}

int main()
{
    freopen("problem1.in", "r", stdin);
    freopen("problem1.out", "w", stdout);
    scanf("%d", &n);
    if (n == 1)
        print(1, 1), exit(0);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    print(n, 1LL * fac[n] * quick_pow(2, mod - 2) % mod);
    return 0;
}
