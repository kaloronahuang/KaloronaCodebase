// CF341D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1010;

int n, q;

struct BIT
{
    inline int lowbit(int x) { return x & (-x); }

    ll nodes[MAX_N][MAX_N];

    void update(int x, int y, ll d)
    {
        for (int i = x; i <= n; i += lowbit(i))
            for (int j = y; j <= n; j += lowbit(j))
                nodes[i][j] ^= d;
    }

    ll query(int x, int y)
    {
        ll ret = 0;
        for (int i = x; i >= 1; i -= lowbit(i))
            for (int j = y; j >= 1; j -= lowbit(j))
                ret ^= nodes[i][j];
        return ret;
    }
} tr[4];

int getParity(int x, int y) { return (x & 1) | ((y & 1) << 1); }

void modify(int x, int y, ll d) { tr[getParity(x, y)].update(x, y, d); }

ll query(int x, int y) { return tr[getParity(x, y)].query(x, y); }

int main()
{
    scanf("%d%d", &n, &q);
    while (q--)
    {
        int opt, x1, y1, x2, y2;
        ll d;
        scanf("%d%d%d%d%d", &opt, &x1, &y1, &x2, &y2);
        if (opt == 1)
        {
            ll ans = 0;
            ans ^= query(x2, y2);
            ans ^= query(x1 - 1, y2);
            ans ^= query(x2, y1 - 1);
            ans ^= query(x1 - 1, y1 - 1);
            printf("%lld\n", ans);
        }
        else
        {
            scanf("%lld", &d), modify(x1, y1, d);
            modify(x2 + 1, y1, d), modify(x1, y2 + 1, d);
            modify(x2 + 1, y2 + 1, d);
        }
    }
    return 0;
}