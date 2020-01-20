// inverse.cpp
#include <bits/stdc++.h>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

const int MAX_N = 1e6 + 2000, DOM = 1e5 + 20;
typedef long long ll;

int n, ai[MAX_N], nodes[2][MAX_N];
map<int, int> mp;

inline int lowbit(int x) { return x & (-x); }

void update(int id, int x, int d)
{
    for (; x < MAX_N; x += lowbit(x))
        nodes[id][x] += d;
}

int query(int id, int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[id][x];
    return ret;
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
        ai[i] = abs(read()), mp[ai[i]]++;
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        update(0, ai[i] + DOM, 1);
    for (int i = 1; i <= n; i++)
    {
        update(0, ai[i] + DOM, -1);
        ans += min(query(0, ai[i] + DOM - 1), query(1, ai[i] + DOM - 1));
        update(1, ai[i] + DOM, 1);
    }
    printf("%lld\n", ans);
    return 0;
}