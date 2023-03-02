// H.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;
typedef pair<double, double> pdd;
typedef pair<pdd, int> pdi;
typedef pair<pair<int, int>, int> pii;

int n, b, dsiz;
ll val[MAX_N], ansbox[MAX_N], nodes[MAX_N], sxi[MAX_N], syi[MAX_N];
ll xi[MAX_N], yi[MAX_N], cxi[MAX_N], cyi[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, ll d)
{
    for (; x <= dsiz; x += lowbit(x))
        nodes[x] += d;
}

ll query(int x, ll ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

bool cmp1(int lhs, int rhs) { return xi[lhs] * yi[rhs] < xi[rhs] * yi[lhs]; }

bool cmp2(int lhs, int rhs) { return (xi[lhs] - b) * yi[rhs] < (xi[rhs] - b) * yi[lhs]; }

int main()
{
    scanf("%d%d", &n, &b);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld%lld", &xi[i], &yi[i], &val[i]);
        sxi[i] = i, syi[i] = i;
    }
    sort(sxi + 1, sxi + 1 + n, cmp1);
    sort(syi + 1, syi + 1 + n, cmp2);
    for (int i = 1; i <= n; i++)
    {
        cxi[sxi[i]] = i;
        cyi[syi[i]] = i;
    }
    dsiz = n;
    for (int i = n; i >= 1; i--)
    {
        int u = sxi[i];
        ansbox[u] = query(cyi[u]);
        update(cyi[u], val[u]);
    }
    for (int i = 1; i <= n; i++)
        printf("%lld\n", ansbox[i]);
    return 0;
}