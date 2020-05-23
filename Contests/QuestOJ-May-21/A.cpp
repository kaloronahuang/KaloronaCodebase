// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, block = 50;
const double eps = 1e-12;

typedef long double ld;

int n, ai[MAX_N], rk[MAX_N], pre[MAX_N], nxt[MAX_N];
map<int, long double> mp;

int main()
{
    scanf("%d", &n);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &ai[i]), rk[i] = i;
    sort(rk + 1, rk + 1 + n, [](const int &a, const int &b) { return ai[a] < ai[b] || (ai[a] == ai[b] && a < b); });
    for (int i = 1; i <= n; i++)
        pre[i] = i - 1, nxt[i] = i + 1;
    ld ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int pos = rk[i], lft = pos, rig = pos;
        ld lpart = 0, rpart = 0, coeff = 1.0;
        for (int j = 1; j <= block; j++)
        {
            if (lft > 0)
                lpart += coeff * (lft - pre[lft]), lft = pre[lft];
            if (rig <= n)
                rpart += coeff * (nxt[rig] - rig), rig = nxt[rig];
            coeff *= 0.5;
        }
        ans += ai[pos] * lpart * rpart * 0.5;
        nxt[pre[pos]] = nxt[pos], pre[nxt[pos]] = pre[pos];
    }
    printf("%.10Lf\n", ans / (1LL * n * n));
    return 0;
}