// LOJ3248.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, ai[MAX_N], val[MAX_N], idx[MAX_N], q[MAX_N];
pair<int, int> ans[MAX_N];

long long slope(int x, int y, int z) { return 1LL * (ai[z] - ai[x]) * (y - x) - 1LL * (ai[y] - ai[x]) * (z - x); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]), idx[i] = i;
    sort(idx + 1, idx + 1 + n, [](const int &a, const int &b) { return ai[a] < ai[b]; });
    int tail = 0;
    for (int i = n; i >= 1; i--)
    {
        int u = idx[i];
        while (tail && u > q[tail])
            tail--;
        while (tail > 1 && slope(u, q[tail - 1], q[tail]) > 0)
            tail--;
        q[++tail] = u;
        if (ai[u] > ai[val[u]])
        {
            int l = 2, r = tail, res = q[1] > val[u];
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (q[mid] > val[u] && slope(val[u], q[mid - 1], q[mid]) <= 0)
                    res = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
            if (res)
                ans[u] = make_pair(ai[q[res]] - ai[val[u]], q[res] - val[u]);
        }
    }
    tail = 0;
    for (int i = 1; i <= n; i++)
    {
        int u = idx[i];
        while (tail && u < q[tail])
            tail--;
        while (tail > 1 && slope(u, q[tail - 1], q[tail]) > 0)
            tail--;
        q[++tail] = u;
        if (ai[u] < ai[val[u]])
        {
            int l = 2, r = tail, res = q[1] < val[u];
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (q[mid] < val[u] && slope(val[u], q[mid - 1], q[mid]) <= 0)
                    res = mid, l = mid + 1;
                else
                    r = mid - 1;
            }
            if (res)
                ans[u] = make_pair(ai[val[u]] - ai[q[res]], val[u] - q[res]);
        }
    }
    for (int i = 1, d; i <= n; i++)
        if (ans[i].second != 0)
            d = __gcd(ans[i].first, ans[i].second), printf("%d/%d\n", ans[i].first / d, ans[i].second / d);
        else
            puts("-1");
    return 0;
}