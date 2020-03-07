// LOJ534.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 15010;

typedef pair<int, int> pii;

int q, max_v, T, dp[20][MAX_N];
vector<pii> nodes[MAX_N << 2];
bool vis[MAX_N << 2];
pii last_ans;

char nc()
{
    static char buff[1 << 20], *p1 = buff, *p2 = buff;
    return p1 == p2 && (p2 = ((p1 = buff) + fread(buff, 1, 1 << 20, stdin)), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
        f = (c == '-') ? -1 : f, c = nc();
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return x * f;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int ql, int qr, int l, int r, int p, int volumn, int weight)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p].push_back(make_pair(volumn, weight)));
    if (ql <= mid)
        update(ql, qr, l, mid, lson, volumn, weight);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, volumn, weight);
}

pii query(int qx, int l, int r, int p, int val, int dep)
{
    if (!vis[p])
    {
        memcpy(dp[dep], dp[dep - 1], sizeof(dp[dep]));
        for (auto x : nodes[p])
            for (int i = max_v; i >= x.first; i--)
                dp[dep][i] = max(dp[dep][i], dp[dep][i - x.first] + x.second);
        vis[p] = true;
    }
    if (l == r)
        return make_pair(dp[dep][val] >= 0, max(dp[dep][val], 0));
    if (qx <= mid)
        return query(qx, l, mid, lson, val, dep + 1);
    else
        return query(qx, mid + 1, r, rson, val, dep + 1);
}

#undef mid
#undef rson
#undef lson

int main()
{
    memset(dp, 0xbf, sizeof(dp)), dp[0][0] = 0;
    q = read(), max_v = read(), T = read();
    for (int i = 1, op, v, w, e, ans = 0; i <= q; i++)
    {
        op = read(), ans *= T;
        if (op == 1)
        {
            v = read(), w = read(), e = read();
            v -= ans, w -= ans, e -= ans;
            update(i, e, 1, q, 1, v, w);
        }
        else
        {
            v = read(), v -= ans, last_ans = query(i, 1, q, 1, v, 1);
            ans = last_ans.first ^ last_ans.second;
            printf("%d %d\n", last_ans.first, last_ans.second);
        }
    }
    return 0;
}