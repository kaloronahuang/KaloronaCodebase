// UOJ480.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 160;

typedef pair<int, int> pii;
typedef long long ll;

int T, n, K, L;
pii arr[MAX_N];
ll pre[MAX_N][MAX_N], suf[MAX_N][MAX_N][MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(pre, 0, sizeof(pre)), memset(suf, 0, sizeof(suf));
        scanf("%d%d%d", &n, &K, &L);
        for (int i = 1; i <= n; i++)
            scanf("%d", &arr[i].first);
        for (int i = 1; i <= n; i++)
            scanf("%d", &arr[i].second);
        sort(arr + 1, arr + 1 + n), reverse(arr + 1, arr + 1 + n);
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= i; j++)
            {
                pre[i][j] = pre[i - 1][j] + arr[i].first;
                if (j > 0)
                    pre[i][j] = max(pre[i][j], pre[i - 1][j - 1] + arr[i].first + arr[i].second);
            }
        for (int i = n; i >= 1; i--)
            for (int b = 0; b <= (n - i + 1); b++)
                for (int ab = 0; ab + b <= (n - i + 1); ab++)
                {
                    suf[i][b][ab] = suf[i + 1][b][ab];
                    if (b > 0)
                        suf[i][b][ab] = max(suf[i][b][ab], suf[i + 1][b - 1][ab] + arr[i].second);
                    if (ab > 0)
                        suf[i][b][ab] = max(suf[i][b][ab], suf[i + 1][b][ab - 1] + arr[i].first + arr[i].second);
                }
        ll ans = 0;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= i; j++)
                for (int k = 0; k <= n - i; k++)
                    if (j + k >= L && i + k == K && K >= j + k)
                        ans = max(ans, pre[i][j] + suf[i + 1][K - j - k][k]);
        printf("%lld\n", ans);
    }
    return 0;
}