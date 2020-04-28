// P3589.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, a, b, p, m, ltot;
char str[MAX_N];
pair<int, int> limits[MAX_N << 2];

void create(int l, int r)
{
    if (l <= r)
        limits[++ltot] = make_pair(l, r);
    else
        limits[++ltot] = make_pair(l, n - 1), limits[++ltot] = make_pair(0, r);
}

int main()
{
    scanf("%d%d%d%d%d%s", &n, &a, &b, &p, &m, str);
    int ans = 0;
    for (int i = 0; i < m; i++)
        if (str[i] == '0')
            create((p + n - 1LL * i * a % n) % n, (0LL + n - 1 - 1LL * i * a % n) % n);
        else
            create((n - 1LL * i * a % n) % n, (p + n - 1LL * i * a % n - 1) % n);
    for (int i = 1; i < m; i++)
        create((0LL + b + n - 1LL * a * i % n) % n, (0LL + b + n - 1LL * a * i % n) % n);
    sort(limits + 1, limits + 1 + ltot);
    int tmp = -1;
    for (int i = 1; i <= ltot; i++)
    {
        if (limits[i].first > tmp)
            ans += limits[i].first - tmp - 1, tmp = limits[i].second;
        else
            tmp = max(tmp, limits[i].second);
    }
    printf("%d\n", ans + n - 1 - tmp);
    return 0;
}