// CF1136D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5e5 + 2000;
int arr[MAX_N], n, m, tmpx, tmpy, ans;
bool vis[MAX_N];
vector<int> cond[MAX_N];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), cond[tmpx].push_back(tmpy);
    vis[arr[n]] = true;
    for (int i = n - 1; i >= 1; i--)
    {
        int cnt = 0, siz = cond[arr[i]].size();
        for (int j = 0; j < siz; j++)
            if (vis[cond[arr[i]][j]])
                cnt++;
        if (cnt + ans + i == n)
            ans++;
        else
            vis[arr[i]] = true;
    }
    printf("%d", ans);
    return 0;
}