// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

ll f[MAX_N], data[MAX_N], h;
int x, y, z;

int main()
{
    scanf("%lld%d%d%d", &h, &x, &y, &z);
    memset(f, 0x3f, sizeof(f)), h--;
    int head = 0, tail = 1;
    data[1] = 0, f[0] = 0;
    while (head++ < tail)
    {
        if (data[head] + y < f[(data[head] + y) % x])
            f[(data[++tail] = data[head] + y) % x] = data[head] + y;
        if (data[head] + z < f[(data[head] + z) % x])
            f[(data[++tail] = data[head] + z) % x] = data[head] + z;
    }
    ll ans = 0;
    for (int i = 0; i < x; i++)
        if (h >= f[i])
            ans += (h - f[i]) / x + 1;
    printf("%lld", ans);
    return 0;
}