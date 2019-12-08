// CF1264A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 2000;

int T, n, pi[MAX_N], cnt;
pair<int, int> prs[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), pi[n + 1] = cnt = 0;
        memset(prs, 0, sizeof(prs));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &pi[i]);
            if (pi[i] != pi[i - 1])
                prs[++cnt] = make_pair(pi[i], 0);
            prs[cnt].second++;
        }
        int gold = prs[1].second, silver = 0, bronze = 0, ptr = 2;
        while (silver <= gold && ptr <= cnt)
            silver += prs[ptr++].second;
        while (bronze <= gold && ptr <= cnt)
            bronze += prs[ptr++].second;
        while (gold + silver + bronze + prs[ptr].second <= (n >> 1) && ptr <= cnt)
            bronze += prs[ptr++].second;
        if (gold < silver && gold < silver && (gold + silver + bronze) <= (n >> 1))
            printf("%d %d %d\n", gold, silver, bronze);
        else
            puts("0 0 0");
    }
    return 0;
}