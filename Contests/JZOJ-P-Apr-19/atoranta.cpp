// atoranta.cpp
// #pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, q, mu[MAX_N], primes[MAX_N], tot, mem[MAX_N], size[MAX_N], last_time[MAX_N], visit[MAX_N];
ll ans[MAX_N], sum;
bool vis[MAX_N];
stack<int> stk;

struct node
{
    int id, time_frame;
};
vector<node> frames[MAX_N], qframes[MAX_N];
vector<int> facts[MAX_N];

struct segment
{
    int x, y, z;
} org[MAX_N], qseg[MAX_N];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

void sieve()
{
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true, mu[i * primes[j]] = -mu[i];
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
        }
    }
    for (int i = 2; i < MAX_N; i++)
        if (!vis[i])
            for (int j = i; j <= 1e6; j += i)
                facts[j].push_back(i);
}

int find(int x)
{
    while (mem[x])
        x = mem[x];
    return x;
}

void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (size[fx] < size[fy])
        swap(fx, fy);
    mem[fy] = fx, sum += 1LL * size[fx] * size[fy];
    size[fx] += size[fy], stk.push(fy);
}

void undo()
{
    int fy = stk.top(), fx = mem[fy];
    size[fx] -= size[fy], sum -= 1LL * size[fx] * size[fy], mem[fy] = 0;
    stk.pop();
}

void insert(int w, int id, int time_frame)
{
    node u = node{id, time_frame};
    int m = facts[w].size();
    for (int stat = 0; stat < (1 << m); stat++)
    {
        int pans = 1;
        for (int i = 0; i < m; i++)
            if (stat & (1 << i))
                pans *= facts[w][i];
        frames[pans].push_back(u);
    }
}

void solve(int x)
{
    sum = 0;
    for (int i = 0, gx, siz = frames[x].size(); i < siz; i = gx + 1)
    {
        gx = i - 1;
        int ctime = frames[x][i].time_frame;
        while (gx < siz - 1 && frames[x][gx + 1].time_frame == ctime)
            gx++, merge(org[frames[x][gx].id].x, org[frames[x][gx].id].y);
        ll pans = 1LL * mu[x] * sum;
        if (ctime != -1)
        {
            ans[ctime] += pans;
            for (int tot = i; tot <= gx; tot++)
                undo();
        }
        else
        {
            for (int k = gx + 1; k < siz; k++)
                visit[frames[x][k].time_frame] = x;
            for (int k = 0; k <= q; k++)
                if (visit[k] != x)
                    ans[k] += pans;
        }
    }
    while (!stk.empty())
        undo();
}

int main()
{
    fileIO("atoranta8");
    scanf("%d", &n), sieve();
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d%d", &org[i].x, &org[i].y, &org[i].z);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &qseg[i].x, &qseg[i].y), last_time[qseg[i].x] = i;
    for (int i = 1; i < n; i++)
        if (last_time[i] == 0)
            insert(org[i].z, i, -1);
    for (int i = 1; i <= q; i++)
    {
        node u = node{qseg[i].x, qseg[i].y};
        // marks;
        for (int j = i; j <= q; j++)
            if (j == i || qseg[i].x != qseg[j].x)
                qframes[j].push_back(u);
            else
                break;
        bool flag = false;
        for (int j = 1; j < i; j++)
            if (qseg[i].x == qseg[j].x)
            {
                flag = true;
                break;
            }
        // first;
        if (!flag)
        {
            node v = node{qseg[i].x, org[qseg[i].x].z};
            for (int j = 0; j < i; j++)
                qframes[j].push_back(v);
        }
    }
    for (int i = 0; i <= q; i++)
        for (int j = 0, siz = qframes[i].size(); j < siz; j++)
            insert(qframes[i][j].time_frame, qframes[i][j].id, i);
    for (int i = 1; i <= n; i++)
        size[i] = 1;
    for (int i = 1; i <= 1e6; i++)
        if (!frames[i].empty())
            solve(i);
    for (int i = 0; i <= q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}