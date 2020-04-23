// sorts2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N], idx[MAX_N];
bool vis[MAX_N];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

int main()
{
    // fileIO("sorts2");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), idx[i] = i;
    sort(idx + 1, idx + 1 + n, [](const int &rhs1, const int &rhs2) { return ai[rhs1] < ai[rhs2]; });
    int cnt = 0, ans = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i < idx[i])
            cnt++;
        if (vis[i])
            cnt--;
        vis[idx[i]] = true, ans = max(ans, cnt);
    }
    printf("%d\n", ans);
    return 0;
}