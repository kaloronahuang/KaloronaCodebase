// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_K = 50010;
typedef long long ll;

int n, k, max_price, pos[MAX_K], ptot;
vector<ll> store[330];
ll dp[330][MAX_K];

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

void solve(int idx, int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    int mid = (LB + RB) >> 1, gpt = l;
    for (int i = max(l, int(mid - store[idx].size())); i <= min(mid, r); i++)
        if (dp[idx][pos[mid]] < dp[idx - 1][pos[i]] + (i == mid ? 0 : store[idx][mid - i - 1]))
            gpt = i, dp[idx][pos[mid]] = dp[idx - 1][pos[i]] + (i == mid ? 0 : store[idx][mid - i - 1]);
    solve(idx, l, gpt, LB, mid - 1), solve(idx, gpt, r, mid + 1, RB);
}

int main()
{
    n = read(), k = read();
    for (int i = 1, c, v; i <= n; i++)
        c = read(), v = read(), store[c].push_back(v), max_price = max(max_price, c);
    for (int i = 1; i <= max_price; i++)
    {
        sort(store[i].begin(), store[i].end());
        reverse(store[i].begin(), store[i].end());
        for (int j = 1, siz = store[i].size(); j < siz; j++)
            store[i][j] += store[i][j - 1];
    }
    for (int price = 1; price <= max_price; price++)
        for (int start_pos = 0; start_pos < price; start_pos++)
        {
            ptot = 0;
            for (int i = start_pos; i <= k; i += price)
                pos[++ptot] = i;
            solve(price, 1, ptot, 1, ptot);
        }
    for (int i = 1; i <= k; i++)
        printf("%lld ", dp[max_price][i]);
    putchar('\n');
    return 0;
}