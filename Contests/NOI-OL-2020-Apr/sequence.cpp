// sequence.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, ai[MAX_N], bucket[MAX_N];
vector<int> mp;

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return f * x;
}

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

namespace subtask1
{

int handler()
{
    int ans = 0;
    for (int r = 1; r <= n; r++)
    {
        int cnt = 0;
        for (int l = r; l >= 1; l--)
        {
            if (bucket[ai[l]] == 0)
                cnt++;
            bucket[ai[l]]++;
            ans = (0LL + ans + 1LL * cnt * cnt % mod) % mod;
        }
        for (int l = r; l >= 1; l--)
            bucket[ai[l]]--;
    }
    printf("%d\n", ans);
    return 0;
}

} // namespace subtask1

int main()
{
    fileIO("sequence");
    n = read();
    for (int i = 1; i <= n; i++)
        ai[i] = read(), mp.push_back(ai[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        ai[i] = ripe(ai[i]);
    if (n <= 1000)
        return subtask1::handler();
    return 0;
}