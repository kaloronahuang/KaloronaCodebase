// P1315.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10100;

int n, m, k, di[MAX_N], ti[MAX_N], ai[MAX_N], bi[MAX_N];
int latest[MAX_N], cnt[MAX_N], sttime[MAX_N], arrive[MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &di[i]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &ti[i], &ai[i], &bi[i]);
        cnt[bi[i]]++;
        latest[ai[i]] = max(latest[ai[i]], ti[i]);
    }
    int tim = 0;
    for (int i = 1; i <= n; i++)
    {
        arrive[i] = tim;
        tim = max(tim, latest[i]), tim += di[i];
    }
    int mx_val = 0, mx_pos = -1;
    while (k--)
    {
        mx_val = 0;
        for (int i = 2; i <= n; i++)
        {
            if (di[i - 1] == 0)
                continue;
            int tmp_cnt = 0;
            for (int j = i; j <= n; j++)
            {
                tmp_cnt += cnt[j];
                if (arrive[j] <= latest[j])
                    break;
            }
            if (tmp_cnt > mx_val)
                mx_val = tmp_cnt, mx_pos = i;
        }
        di[mx_pos - 1]--;
        for (int i = mx_pos; i <= n; i++)
        {
            arrive[i]--;
            if (arrive[i] < latest[i])
                break;
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans += arrive[bi[i]] - ti[i];
    printf("%d", ans);
    return 0;
}