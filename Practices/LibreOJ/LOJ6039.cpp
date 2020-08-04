// LOJ6039.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, MAX_K = 5e4 + 200, MAX_C = 330;

typedef long long ll;

int n, m, pos[MAX_N], ptot;
ll dp[MAX_C][MAX_K];
deque<ll> prefix[MAX_C];

void solve(int cid, int cost, int l, int r, int L, int R)
{
    if (l > r || L > R)
        return;
    int mid = (l + r) >> 1, gpt = -1;
    for (int i = L; i <= min(R, mid); i++)
        if ((mid - i <= prefix[cost].size() - 1) && (gpt == -1 || dp[cid - 1][pos[gpt]] + prefix[cost][mid - gpt] < dp[cid - 1][pos[i]] + prefix[cost][mid - i]))
            gpt = i;
    if (l == r)
        return (void)(dp[cid][pos[mid]] = dp[cid - 1][pos[gpt]] + prefix[cost][mid - gpt]);
    solve(cid, cost, l, mid, L, gpt), solve(cid, cost, mid + 1, r, gpt, R);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, c, v; i <= n; i++)
        scanf("%d%d", &c, &v), prefix[c].push_back(v);
    for (int i = 1; i < MAX_C; i++)
        if (!prefix[i].empty())
        {
            sort(prefix[i].begin(), prefix[i].end()), reverse(prefix[i].begin(), prefix[i].end());
            for (int j = 1, siz = prefix[i].size(); j < siz; j++)
                prefix[i][j] += prefix[i][j - 1];
            prefix[i].push_front(0);
        }
    int ctot = 0;
    for (int i = 1; i < MAX_C; i++)
        if (!prefix[i].empty())
        {
            ctot++;
            for (int start_pos = 0; start_pos < i; start_pos++)
            {
                ptot = 0;
                for (int p = start_pos; p <= m; p += i)
                    pos[++ptot] = p;
                solve(ctot, i, 1, ptot, 1, ptot);
            }
        }
    for (int i = 1; i <= m; i++)
        printf("%lld ", dp[ctot][i]);
    puts("");
    return 0;
}