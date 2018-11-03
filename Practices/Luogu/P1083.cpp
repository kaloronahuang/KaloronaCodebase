// P1083.cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1001000;
const int INF = 0x7fffffff;
int n, m;
int r[maxn], d[maxn], s[maxn], t[maxn];

struct BIT
{
    int Cmin[maxn];
    int C[maxn];

    BIT()
    {
        fill(Cmin, Cmin + maxn, INF);
    }

    inline int lowbit(int x)
    {
        return x & -x;
    }

    void Add(int x, int d)
    {
        while (x <= n)
        {
            C[x] += d;
            Cmin[x] = min(Cmin[x], C[x]);
            x = lowbit(x);
        }
    }

    int QueryMin(int x, int y)
    {
        int res = INF;
        while (y >= x)
        {
            res = min(res, Cmin[y]);
            y--;
            for (; y - lowbit(y) >= x; y -= lowbit(y))
                res = min(res, Cmin[y]);
        }
        return res;
    }
};

void solve()
{
    for (int i = 1; i <= m; i++)
    {
    }
}

int main()
{
    // I/O;
    cin >> n >> m;
    BIT table;
    for (int i = 1; i <= n; i++)
        scanf("%d", &r[i]), table.Add(i, r[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &d[i], &s[i], &t[i]);

    return 0;
}