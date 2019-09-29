// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, MAX_L = 1e6 + 200;

int n, L, A, B;
bool vis[MAX_L], flag;
int dp[MAX_L];

struct node
{
    int lft, rig;
} nodes[MAX_N];
deque<node> dq;

int main()
{
    scanf("%d%d%d%d", &n, &L, &A, &B);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nodes[i].lft, &nodes[i].rig), flag |= ((nodes[i].rig - nodes[i].lft) > (B << 1));
    if (flag)
        puts("-1"), exit(0);
    vis[0] = 1;
    for (int i = 1; i <= L; i++)
        vis[i] = true, dp[i] = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++)
        for (int j = nodes[i].lft + 1; j < nodes[i].rig; j++)
            vis[j] = false;
    dq.push_back(node{0, 0});
    for (int i = (A << 1); i <= L; i += 2)
    {
        int tmp = i - (A << 1);
        if (vis[tmp])
        {
            while (!dq.empty() && dq.back().rig >= dp[tmp])
                dq.pop_back();
            dq.push_back(node{tmp, dp[tmp]});
        }
        tmp = i - (B << 1);
        while (!dq.empty() && dq.front().lft < tmp)
            dq.pop_front();
        if (vis[i] && !dq.empty())
            dp[i] = dq.front().rig + 1;
    }
    if (dp[L] >= 0x3f3f3f3f)
        puts("-1");
    else
        printf("%d", dp[L]);
    return 0;
}