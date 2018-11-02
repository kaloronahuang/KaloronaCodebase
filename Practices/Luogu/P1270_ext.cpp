#include <bits/stdc++.h>
#define v first
#define w second
using namespace std;
const int maxn = 600 + 10;
int n = 1, tim;
int f[maxn][maxn]; //在结点i偷到j幅画的最少时间
int c[maxn];
vector< pair<int, int> > G[maxn];

void read(int u)
{
    int w, val;
    scanf("%d%d", &w, &val);
    if (val)
    { //处理递归终点
        G[u].push_back(make_pair(++n, w));
        c[n] = val;
        return;
    }
    G[u].push_back(make_pair(++n, w));
    int v = n;
    read(v);
    read(v);
    //读入v的两个儿子
}

void input()
{
    cin >> tim;
    read(1);
}

void dp(int u)
{
    if (G[u].empty())
    {
        for (int i = 0; i <= c[u]; ++i)
            f[u][i] = i * 5;
        return;
    }
    if (u == 1)
    {
        dp(G[u][0].v);
        f[u][0] = 0;
        for (int i = 1; i <= 600; ++i)
            f[u][i] = f[G[u][0].v][i] + G[u][0].w * 2;
        return;
    }
    dp(G[u][0].v);
    dp(G[u][1].v);
    for (int i = 0; i <= 600; ++i)
        for (int j = 0; i + j <= 600; ++j)
        {
            //经分析可知，每一层偷到的画不足120幅，这里用不影响效率的充分大数来代替
            int lw = i ? G[u][0].w : 0, rw = j ? G[u][1].w : 0;
            f[u][i + j] = min(f[u][i + j], f[G[u][0].v][i] + f[G[u][1].v][j] + lw * 2 + rw * 2);
        }
}

void solve()
{
    memset(f, 0x3f, sizeof(f));
    dp(1);
    int ans = 0;
    for (int i = 1; i <= 600; ++i)
        if (f[1][i] < tim)
            ans = i;
    cout << ans;
}

int main()
{
    input();
    solve();
    return 0;
}