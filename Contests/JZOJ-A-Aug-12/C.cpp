// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, INF = 0x3f3f3f3f;

int head[MAX_N], current, n, done, block_tot, ptot, curtbit[MAX_N], nxtbit[MAX_N];
int dp[223321][MAX_N], d[223321][MAX_N];
char opt[MAX_N][MAX_N];
bool tag[MAX_N], legal[223321];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N * 2];

struct point
{
    int x, y, val;
    bool operator<(const point &pt) const { return x < pt.x || (x == pt.x && y < pt.y); }
} pts[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void match(int u)
{
    if (u <= n)
        pts[block_tot].x++;
    else
        pts[block_tot].y++;
    tag[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!tag[edges[i].to])
            match(edges[i].to);
}

void check(int x)
{
    int now = x, px = 0, py = 0;
    for (int i = ptot; i >= 1; i--)
        while (now >= curtbit[i])
            d[x][i]++, px += pts[i].x, py += pts[i].y, now -= curtbit[i];
    legal[x] = (px == py);
}

int main()
{
    freopen("factory.in", "r", stdin);
    freopen("factory.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", opt[i] + 1);
        for (int j = 1; j <= n; j++)
            if (opt[i][j] == '1')
                done++, addpath(i, n + j), addpath(n + j, i);
    }

    for (int i = n + 1; i <= (n << 1); i++)
        if (!tag[i])
            block_tot++, match(i);

    for (int i = 1; i <= n; i++)
        if (!tag[i])
            pts[++block_tot] = point{1, 0, 0};

    sort(pts + 1, pts + 1 + block_tot);
    ptot = 1, pts[1].val = 1;
    for (int i = 2; i <= block_tot; i++)
        if (pts[i].x != pts[i - 1].x || pts[i].y != pts[i - 1].y)
            pts[++ptot] = point{pts[i].x, pts[i].y, 1};
        else
            pts[ptot].val++;

    curtbit[1] = 1, nxtbit[1] = pts[1].val;
    for (int i = 2; i <= ptot; i++)
        curtbit[i] = nxtbit[i - 1] + 1, nxtbit[i] = nxtbit[i - 1] + curtbit[i] * pts[i].val;

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= ptot; i++)
        dp[curtbit[i]][pts[i].x] = 0;
    for (int i = 1; i <= nxtbit[ptot]; i++)
        check(i);

    for (int i = 0; i <= nxtbit[ptot]; i++)
        for (int j = 1; j <= ptot; j++)
        {
            if (d[i][j] == pts[j].val)
                continue;
            for (int k = 0; k <= n; k++)
            {
                if (dp[i][k] == INF)
                    continue;
                dp[i + curtbit[j]][k + pts[j].x] = min(dp[i][k], dp[i + curtbit[j]][k + pts[j].x]);
                if (legal[i + curtbit[j]])
                    dp[i + curtbit[j]][0] = min(dp[i + curtbit[j]][0], dp[i + curtbit[j]][k + pts[j].x] + (k + pts[j].x) * (k + pts[j].x));
            }
        }
    printf("%d", dp[nxtbit[ptot]][0] - done);
    return 0;
}