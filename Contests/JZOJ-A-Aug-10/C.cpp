// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 2000, mod = 1e9;

int head[MAX_N], current, n, tot;
ll global_sum = 0, ans = 0;
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct point
{
    int x, y;
    bool operator<(const point &pt) const { return x < pt.x || (x == pt.x && y < pt.y); }
} pts[MAX_N];

struct node
{
    int x, y1, y2, val;
} vec[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void swap()
{
    for (int i = 1; i <= n; i++)
        swap(pts[i].x, pts[i].y);
}

void build_tree()
{
    memset(head, -1, sizeof(head));
    current = 0;
    sort(pts + 1, pts + 1 + n);
    tot = 0;
    int cursor = 1;
    while (cursor <= n)
    {
        int nd = ++tot;

        int endpoint = cursor + 1;
        while (pts[endpoint].x == pts[cursor].x && pts[endpoint].y == pts[endpoint - 1].y + 1)
            endpoint++;
        endpoint--;

        vec[tot] = (node{pts[cursor].x, pts[cursor].y, pts[endpoint].y, endpoint - cursor + 1});
        cursor = endpoint + 1;
    }

    int cursor1 = 0, cursor2 = 1;
    while (cursor2 <= tot)
    {
        while (vec[cursor1].x < vec[cursor2].x - 1 || (vec[cursor1].x == vec[cursor2].x - 1 && vec[cursor1].y2 < vec[cursor2].y1))
            cursor1++;
        bool flag = false;
        while (vec[cursor1].x == vec[cursor2].x - 1 && vec[cursor1].y1 <= vec[cursor2].y2)
        {
            flag = true;
            addpath(cursor1, cursor2), addpath(cursor2, cursor1);
            cursor1++;
        }
        if (flag)
            cursor1--;
        cursor2++;
    }
}

ll dfs(int u, int fat)
{
    ll answer = vec[u].val;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            (answer += dfs(edges[i].to, u)) %= mod;
    ans = (ans + answer * (global_sum - answer)) % mod;
    return answer;
}

ll calc()
{
    global_sum = 0, ans = 0;
    for (int i = 1; i <= tot; i++)
        (global_sum += vec[i].val) %= mod;
    dfs(1, 0);
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &pts[i].x, &pts[i].y);
    ll answer = 0;
    build_tree(), answer += calc();
    answer %= mod;
    swap();
    build_tree(), answer += calc();
    answer %= mod;
    printf("%lld", answer);
    return 0;
}