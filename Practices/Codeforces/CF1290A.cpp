// CF1290A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4040;

int T, n, m, limit, ai[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &n, &m, &limit);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        limit = min(limit, m - 1);
        int len = n - m + 1, gans = -1;
        for (int lft = 0; lft <= limit; lft++)
        {
            int rig = limit - lft, pans = 0x3f3f3f3f;
            int l = lft + 1, r = n - rig;
            for (int i = l; i + len - 1 <= r; i++)
                pans = min(pans, max(ai[i], ai[i + len - 1]));
            gans = max(gans, pans);
        }
        printf("%d\n", gans);
    }
    return 0;
}