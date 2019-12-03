// YBT-OJ1673.cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 1e6 + 200;

ll n, m, hi[MAX_N], vi[MAX_N];

inline char gc()
{
    static const int IN_LEN = (1 << 20);
    static char buf[IN_LEN], *s, *t;
    return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}

ll read()
{
    ll x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return x * f;
}

int main()
{
    priority_queue<pr> pq;
    n = read(), m = read() + 1;
    for (int i = 1; i <= n; i++)
        hi[i] = read(), vi[i] = read();
    ll ans = 0, gans = 0, tlen = 0, tval = 0;
    for (int i = 1; i <= n; i++)
    {
        m--, ans += vi[i];
        if (m == 0)
            break;
        if (hi[i] > 1)
        {
            pq.push(make_pair(-vi[i], hi[i] - 1));
            tlen += hi[i] - 1, tval += 1LL * (hi[i] - 1) * vi[i];
            while (!pq.empty() && tlen - pq.top().second >= m)
            {
                tlen -= pq.top().second;
                tval += 1LL * pq.top().first * pq.top().second;
                pq.pop();
            }
        }
        gans = max(gans, tlen >= m ? (0LL + ans + tval + 1LL * pq.top().first * pq.top().second - 1LL * (pq.top().second - (tlen - m)) * pq.top().first) : (ans + tval));
    }
    printf("%lld\n", gans);
    return 0;
}