// P3998.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100;

int n, m, tmpx, tmpy, cnt[MAX_N], ans[MAX_N];
char opt[10];
set<int> st[MAX_N];
set<int>::iterator it;

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        scanf("%s", opt + 1);
        if (opt[1] == '+')
        {
            scanf("%d%d", &tmpx, &tmpy);
            ans[tmpx] -= cnt[tmpy], ans[tmpy] -= cnt[tmpx];
            st[tmpx].insert(tmpy), st[tmpy].insert(tmpx);
        }
        else if (opt[1] == '-')
        {
            scanf("%d%d", &tmpx, &tmpy);
            ans[tmpx] += cnt[tmpy], ans[tmpy] += cnt[tmpx];
            st[tmpx].erase(st[tmpx].find(tmpy)), st[tmpy].erase(st[tmpy].find(tmpx));
        }
        else
            scanf("%d", &tmpx), cnt[tmpx]++;
    }
    // unlock manually;
    for (int i = 1; i <= n; i++)
        for (it = st[i].begin(); it != st[i].end(); it++)
            ans[i] += cnt[*it];
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}