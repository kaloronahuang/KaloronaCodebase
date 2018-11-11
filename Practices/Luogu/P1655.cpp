// P1655.cpp
#include <iostream>
#include <cstdio>

using namespace std;

#define ull unsigned long long
const int maxn = 101;
ull level[maxn];
ull ans = 0;

ull solve(int n, int m)
{
    if (n > m)
        return level[m] * solve(n - m, m);
    else
        return level[m] / level[m - n];
}

int main()
{
    int a, b;
    level[0] = 1;
    for (int i = 1; i < maxn; i++)
        level[i] = level[i - 1] * i;
    while (scanf("%d%d", &a, &b) != EOF)
    {
        ull ans = solve(a, b);
        cout << ans;
    }
    return 0;
}