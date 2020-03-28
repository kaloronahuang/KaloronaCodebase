// BZ3174.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, h, ai[MAX_N], bi[MAX_N], idx[MAX_N], f[MAX_N], ans;

int main()
{
    scanf("%d", &n), memset(f, -1, sizeof(f)), f[0] = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]), idx[i] = i, f[0] += ai[i];
    scanf("%d", &h);
    sort(idx + 1, idx + 1 + n, [](const int &a, const int &b) { return ai[a] + bi[a] < ai[b] + bi[b]; });
    for (int i = 1; i <= n; i++)
        for (int j = ans; j >= 0; j--)
        {
            if (f[j] + bi[idx[i]] >= h)
                f[j + 1] = max(f[j + 1], f[j] - ai[idx[i]]);
            if (f[ans + 1] >= 0)
                ans++;
        }
    printf("%d\n", ans);
    return 0;
}