// cowdate.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1000000 + 200;

typedef long double ld;

int n, pi[MAX_N], ans;

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

int main()
{
    // fileIO("cowdate");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), ans = max(ans, pi[i]);
    if (ans >= 5e5)
        printf("%d\n", ans), exit(0);
    int rptr = 1;
    ld acc = pi[1], prod = 1000000 - pi[1];
    while (rptr < n && prod > acc)
    {
        rptr++, acc = acc * (1000000 - pi[rptr]) / 1000000 + pi[rptr] * prod / 1000000;
        prod = prod * (1000000 - pi[rptr]) / 1000000;
    }
    ans = max(ans, int(acc));
    for (int lptr = 2; lptr <= n; lptr++)
    {
        prod = prod * 1000000 / (1000000 - pi[lptr - 1]);
        acc = (acc * 1000000 - pi[lptr - 1] * prod) / (1000000 - pi[lptr - 1]);
        while (rptr < n && prod > acc)
        {
            rptr++, acc = acc * (1000000 - pi[rptr]) / 1000000 + pi[rptr] * prod / 1000000;
            prod = prod * (1000000 - pi[rptr]) / 1000000;
        }
        ans = max(ans, int(acc));
    }
    printf("%d\n", ans);
    return 0;
}