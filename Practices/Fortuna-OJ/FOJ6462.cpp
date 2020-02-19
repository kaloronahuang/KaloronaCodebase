// FOJ6462.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, pi[MAX_N], st[2][20][MAX_N], lg[MAX_N];

struct node
{
    int odd, x, y, l, r;
    bool operator<(const node &rhs) const { return pi[x] > pi[rhs.x]; }
};

int rmq(int bit, int l, int r)
{
    int k = lg[r - l + 1];
    return pi[st[bit][k][l]] <= pi[st[bit][k][r - (1 << k) + 1]] ? st[bit][k][l] : st[bit][k][r - (1 << k) + 1];
}

int main()
{
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    scanf("%d", &n), pi[0] = n + 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), st[i & 1][0][i] = i, st[!(i & 1)][0][i] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
        {
            st[0][i][j] = pi[st[0][i - 1][j]] <= pi[st[0][i - 1][j + (1 << (i - 1))]] ? st[0][i - 1][j] : st[0][i - 1][j + (1 << (i - 1))];
            st[1][i][j] = pi[st[1][i - 1][j]] <= pi[st[1][i - 1][j + (1 << (i - 1))]] ? st[1][i - 1][j] : st[1][i - 1][j + (1 << (i - 1))];
        }
    priority_queue<node> pq;
    int x = rmq(1, 1, n), y = rmq(0, x, n);
    pq.push(node{1, x, y, 1, n});
    while (!pq.empty())
    {
        node u = pq.top();
        pq.pop();
        printf("%d %d ", pi[u.x], pi[u.y]);
        if (u.l < u.x)
            x = rmq(u.odd, u.l, u.x - 1), y = rmq(u.odd ^ 1, x, u.x - 1), pq.push(node{u.odd, x, y, u.l, u.x - 1});
        if (u.x < u.y - 1)
            x = rmq(u.odd ^ 1, u.x + 1, u.y - 1), y = rmq(u.odd, x, u.y - 1), pq.push(node{u.odd ^ 1, x, y, u.x + 1, u.x - 1});
        if (u.y < u.r)
            x = rmq(u.odd, u.y + 1, u.r), y = rmq(u.odd ^ 1, x, u.r), pq.push(node{u.odd, x, y, u.y + 1, u.r});
    }
    return 0;
}