// LOJ6241.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int x = 0;
        char c = getchar();
        while (!isdigit(c))
            c = getchar();
        while (isdigit(c))
            x = (1LL * x * 10 % mod + c - '0') % mod, c = getchar();
        printf("%lld\n", (1LL * x * (x + 1) / 2) % mod);
    }
    return 0;
}