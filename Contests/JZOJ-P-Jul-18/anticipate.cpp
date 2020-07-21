// anticipate.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const int MAX_N = 2e5 + 200;
const ld eps = 1e-10;

int T, n, L, R, xi[MAX_N], yi[MAX_N], q[MAX_N];

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

ld calc(ld m, ld x)
{
    if (fabs(m - L) < eps || fabs(m - R) < eps)
        return 0;
    if (x < m)
    {
        ld b = -L * ld(R - L) / ld(m - L);
        return ld(R - L) / ld(m - L) * x + b;
    }
    else
    {
        ld b = -R * ld(L - R) / ld(R - m);
        return ld(L - R) / ld(R - m) * x + b;
    }
}

ld calcMid(int x, int y)
{
    ld l = xi[x], r = xi[y], res = xi[x];
    int cnt = 100;
    while (cnt--)
    {
        ld mid = (l + r) / 2.0;
        if (calc(mid, xi[x]) + yi[x] >= calc(mid, xi[y]) + yi[y])
            l = mid, res = mid;
        else
            r = mid;
    }
    return res;
}

int main()
{
    scanf("%d%d%d%d", &T, &n, &L, &R);
    for (int i = 1; i <= n; i++)
        scanf("%d", &xi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &yi[i]);
    int head = 1, tail = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && calc(xi[i], xi[q[head]]) + yi[q[head]] >= R - L + yi[i])
            tail--;
        while (head <= tail && yi[i] >= yi[q[tail]])
            tail--;
        q[++tail] = i;
    }
    while (head < tail && calc(xi[q[tail - 1]], xi[q[tail]]) + yi[q[tail]] >= R - L + yi[q[tail - 1]])
        tail--;

    return 0;
}