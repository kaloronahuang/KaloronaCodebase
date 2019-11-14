// begin.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n;
ll seqA[MAX_N], seqB[MAX_N], preA[MAX_N], preB[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &seqA[i]), preA[i] = preA[i - 1] + seqA[i];
        for (int i = 1; i <= n; i++)
            scanf("%lld", &seqB[i]), preB[i] = preB[i - 1] + seqB[i];
        if (preA[n] != preB[n])
        {
            puts("-1");
            continue;
        }
        bool flag = true;
        int ans = 0;
        for (int i = 1, rig = 1; i <= n; i++)
        {
            if (seqB[i] == 0)
                continue;
            int lft = rig;
            ans++;
            ll sum = 0;
            while (sum < seqB[i] && rig <= n)
                sum += seqA[rig], rig++;
            if (sum != seqB[i])
            {
                flag = false;
                break;
            }
            if (lft <= i && i <= rig - 1 && seqA[i] == seqB[i])
                ans--;
        }
        if (!flag)
            puts("-1");
        else
            printf("%d\n", ans);
    }
    return 0;
}