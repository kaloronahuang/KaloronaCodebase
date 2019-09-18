// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e7 + 20;

inline ll read()
{
    char ch = getchar();
    ll x = 0, f = 1;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

ll n, num;

int main()
{
    freopen("together.in", "r", stdin);
    freopen("together.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        num ^= read();
    printf("%lld", num);
    return 0;
}