// C.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define pr pair<int, int>
#define ll long long
using namespace std;
const int MAX_N = 24;
ll dp[MAX_N][MAX_N], maps[MAX_N][MAX_N], n, ans = 0;
vector<ll> stat[MAX_N][MAX_N];
bool chk(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= n; }

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lld", &maps[i][j]);
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= n + 1; j++)
            stat[i][j].push_back(0);
    dfs1();
    dfs2();
    printf("%lld", ans);
    return 0;
}