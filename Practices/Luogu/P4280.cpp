// P4280.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200, MAX_K = 110;

typedef long long ll;

int n, limit, ai[MAX_N], pre[MAX_N], suf[MAX_N];

int main()
{
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        if (ai[i] != -1)
            suf[ai[i]]++;
    }
    for (int i = 1; i <= limit; i++)
        suf[i] += suf[i - 1];
    ll ans = 0;
    for (int i = 1, last_choice = 1; i <= n; i++)
    {
        if (ai[i] == -1)
        {
            int val = 0x3f3f3f3f, gpt;
            for (int j = last_choice; j <= limit; j++)
                if (pre[limit] - pre[j] + suf[j - 1] < val)
                    val = pre[limit] - pre[j] + suf[j - 1], gpt = j;
            ans += val, ai[i] = gpt, last_choice = ai[i];
        }
        else
        {
            for (int j = ai[i]; j <= limit; j++)
                suf[j]--;
            ans += pre[limit] - pre[ai[i]];
            for (int j = ai[i]; j <= limit; j++)
                pre[j]++;
        }
    }
    printf("%lld\n", ans);
    return 0;
}