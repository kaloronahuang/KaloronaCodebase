// HDU-3980.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int n, m, T, sg[MAX_N];
bool vis[MAX_N];

int mex(int x)
{
    if (sg[x] != -1)
        return sg[x];
    if (x < m)
        return sg[x] = 0;
    memset(vis, false, sizeof(vis));
    for (int i = m; i <= x; i++)
        vis[mex(i - m) ^ mex(x - i)] = true;
    for (int j = 0;; j++)
        if (!vis[j])
        {
            sg[x] = j;
            break;
        }
    return sg[x];
}

int main()
{
    scanf("%d", &T);
    for (int caseId = 1; caseId <= T; caseId++)
    {
        scanf("%d%d", &n, &m);
        memset(sg, -1, sizeof(sg));
        printf("Case #%d: ", caseId);
        n -= m;
        for (int i = 0; i <= n; i++)
            sg[i] = mex(i);
        if (n < 0)
            puts("abcdxyzk");
        else
            puts(sg[n] ? "abcdxyzk" : "aekdycoin");
    }
    return 0;
}