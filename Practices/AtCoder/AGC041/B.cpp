// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, V, P, ai[MAX_N];

bool check(int mid)
{
    if (ai[mid] + m < ai[P])
        return false;
    long long acc = 0;
    for (int i = P; i <= n; i++)
        if (i != mid && ai[i] < ai[mid] + m)
            acc += min(m, ai[mid] + m - ai[i]);
    return acc >= 1LL * (V - 1) * m;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &V, &P);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    sort(ai + 1, ai + 1 + n), reverse(ai + 1, ai + 1 + n);
    V = max(1, V - P + 1);
    int l = P, r = n, res = P;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            res = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}