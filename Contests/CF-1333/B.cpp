// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, ai[MAX_N], bi[MAX_N], pre[2][MAX_N];

bool judge()
{
    for (int i = 1; i <= n; i++)
    {
        int diff = bi[i] - ai[i];
        if (diff > 0 && !pre[1][i - 1])
            return false;
        else if (diff < 0 && !pre[0][i - 1])
            return false;
    }
    return true;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &ai[i]);
            int bit = 0;
            if (ai[i] == -1)
                bit = 0;
            else if (ai[i] == 1)
                bit = 1;
            pre[0][i] = pre[1][i] = 0;
            if (ai[i] != 0)
                pre[bit][i]++;
            pre[0][i] += pre[0][i - 1], pre[1][i] += pre[1][i - 1];
        }
        for (int i = 1; i <= n; i++)
            scanf("%d", &bi[i]);
        if (judge())
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}