// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 101000;

const double eps = 2e-7;

int n, m, ai[MAX_N], bi[MAX_N];

bool check(double mid)
{
    double tot = m + mid;
    for (int i = 1; i <= n; i++)
    {
        tot -= tot / ai[i];
        if (tot < m && fabs(tot - m) > eps)
            return false;
        tot -= tot / bi[i % n + 1];
        if (tot < m && fabs(tot - m) > eps)
            return false;
    }
    return true;
}

int main()
{
    bool flag = false;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), flag |= (ai[i] == 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]), flag |= (bi[i] == 1);
    if (flag)
        puts("-1"), exit(0);
    double l = eps, r = 1e9, res = -1;
    while (fabs(r - l) >= eps)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            r = mid, res = mid;
        else
            l = mid;
    }
    if (res == -1)
        puts("-1");
    else
        cout << fixed << setprecision(8) << res << endl;
    return 0;
}