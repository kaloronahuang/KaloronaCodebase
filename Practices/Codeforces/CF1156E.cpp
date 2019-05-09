// CF1156E.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 2000;
int n, p[MAX_N], pos[MAX_N], st[20][MAX_N];
long long ans;

int query(int l, int r)
{
    int len = (r - l + 1), k = log2(len);
    if (p[st[k][l]] > p[st[k][r - (1 << k) + 1]])
        return st[k][l];
    else
        return st[k][r - (1 << k) + 1];
}

void solve(int l, int r)
{
    if (l > r || l == r || abs(r - l + 1) <= 2)
        return;
    int curt = query(l, r), num = p[curt];
    solve(l, curt - 1), solve(curt + 1, r);
    if (curt - l > r - curt)
    {
        for (int pt = curt + 1; pt <= r; pt++)
            if (num - p[pt] > 0 && pos[num - p[pt]] < curt && pos[num - p[pt]] >= l)
                ans++;
    }
    else
        for (int pt = l; pt < curt; pt++)
            if (num - p[pt] > 0 && pos[num - p[pt]] <= r && pos[num - p[pt]] > curt)
                ans++;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]), pos[p[i]] = i, st[0][i] = i;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            if (p[st[i - 1][j]] > p[st[i - 1][j + (1 << (i - 1))]])
                st[i][j] = st[i - 1][j];
            else
                st[i][j] = st[i - 1][j + (1 << (i - 1))];
    solve(1, n);
    printf("%lld", ans);
    return 0;
}