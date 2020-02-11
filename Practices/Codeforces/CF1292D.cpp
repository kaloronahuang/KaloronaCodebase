// CF1292D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e3 + 200;

typedef long long ll;

int n, cnt[MAX_N], pre[MAX_N][MAX_N], ptr[MAX_N], sum[MAX_N];
ll ans, curt;

int main()
{
    scanf("%d", &n);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), cnt[val]++;
    // process the fac's factor set;
    for (int i = 2, x; i < MAX_N; i++)
    {
        x = i;
        for (int j = 1; j < MAX_N; j++)
            pre[i][j] = pre[i - 1][j];
        for (int j = 2; 1LL * j * j <= x; j++)
            while (x % j == 0)
                pre[i][j]++, x /= j;
        if (x > 1)
            pre[i][x]++;
    }
    for (int i = 1; i < MAX_N; i++)
        if (cnt[i] == 0)
            ptr[i] = 1;
        else
            for (int j = 1; j <= i; j++)
                if (pre[i][j] > 0)
                    ptr[i] = j, curt += 1LL * pre[i][j] * cnt[i];
    ans = curt;
    while (*max_element(ptr + 1, ptr + MAX_N) > 1)
    {
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < MAX_N; i++)
            sum[ptr[i]] += cnt[i];
        // find the biggest subtree;
        int v = max_element(sum + 1, sum + MAX_N) - sum, siz = sum[v];
        if ((siz << 1) <= n || v == 1)
            break;
        curt -= (siz << 1), curt += n;
        ans = min(ans, curt);
        // go up;
        for (int i = 0; i < MAX_N; i++)
        {
            if (ptr[i] != v)
                ptr[i] = 1;
            if (ptr[i] == 1)
                continue;
            pre[i][ptr[i]]--;
            while (ptr[i] > 1 && pre[i][ptr[i]] == 0)
                ptr[i]--;
        }
    }
    printf("%lld\n", ans);
    return 0;
}