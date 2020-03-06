// LOJ6081.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_W = 330, MAX_K = 1e5 + 200;

int n, k, ptot, pos[MAX_K], max_price;
long long f[MAX_W][MAX_K];
vector<long long> bucket[MAX_W];

void solve(int typ, int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    int mid = (LB + RB) >> 1, gpt = l;
    for (int i = max(l, int(mid - bucket[typ].size())); i <= min(mid, r); i++)
        if (f[typ][pos[mid]] < f[typ - 1][pos[i]] + (i == mid ? 0 : bucket[typ][mid - i - 1]))
            f[typ][pos[mid]] = f[typ - 1][pos[i]] + (i == mid ? 0 : bucket[typ][mid - i - 1]), gpt = i;
    solve(typ, l, gpt, LB, mid - 1), solve(typ, gpt, r, mid + 1, RB);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1, w, v; i <= n; i++)
        scanf("%d%d", &w, &v), bucket[w].push_back(v), max_price = max(max_price, w);
    for (int i = 1; i <= max_price; i++)
    {
        sort(bucket[i].begin(), bucket[i].end()), reverse(bucket[i].begin(), bucket[i].end());
        long long last = 0;
        for (auto &x : bucket[i])
            x += last, last = x;
    }
    for (int price = 1; price <= max_price; price++)
        for (int startPos = 0; startPos < price; startPos++)
        {
            ptot = 0;
            for (int i = startPos; i <= k; i += price)
                pos[++ptot] = i;
            solve(price, 1, ptot, 1, ptot);
        }
    long long max_val = 0;
    for (int i = 1; i <= k; i++)
        max_val = max(max_val, f[max_price][i]), printf("%lld ", max_val);
    putchar('\n');
    return 0;
}