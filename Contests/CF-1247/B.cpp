// B.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, k, d, ai[MAX_N], cnt[MAX_N * 10];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &k, &d);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        int gans = 0, ans = 0x3f3f3f3f;
        for (int i = 1; i <= n; i++)
        {
            gans += (cnt[ai[i]] == 0);
            cnt[ai[i]]++;
            if (i > d)
                gans -= (cnt[ai[i - d]] == 1), cnt[ai[i - d]]--;
            if (i >= d)
                ans = min(ans, gans);
        }
        for (int i = 1; i <= n; i++)
            cnt[ai[i]] = 0;
        printf("%d\n", ans);
    }
    return 0;
}