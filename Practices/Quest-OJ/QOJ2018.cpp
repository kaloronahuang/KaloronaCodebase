// QOJ2018.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 2e5 + 200;

int current, head[MAX_N], deg[MAX_N];
ull ui[MAX_N], vi[MAX_N], A, B, C, n, m;
vector<ull> G1[MAX_N], G2[MAX_N];
bool vis[MAX_N];

ull calc(ull x, ull y) { return (x + y) * (y - x + 1) / 2; }

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%llu%llu", &n, &m), scanf("%llu%llu%llu", &A, &B, &C);
    ull ans0 = 0, ans1 = 0, ans2 = 0, ans3 = 0;
    // calc on ans0;
    for (ull i = 0; i < n; i++)
    {
        ans0 += A * i * ((n - i - 1) * (n - i - 2) / 2);
        ans0 += B * i * ((n - i - 1) * i);
        ans0 += C * i * ((i - 1) * i / 2);
    }
    for (ull i = 1; i <= m; i++)
    {
        scanf("%llu%llu", &ui[i], &vi[i]), deg[ui[i]]++, deg[vi[i]]++;
        if (ui[i] > vi[i])
            swap(ui[i], vi[i]);
        ans1 += A * (ui[i] * (n - ui[i] - 2) + calc(0, ui[i] - 1));
        ans1 += B * (ui[i] * ui[i] + vi[i] * (n - vi[i] - 1) + calc(ui[i] + 1, vi[i] - 1));
        ans1 += C * (vi[i] * (vi[i] - 1) + calc(vi[i] + 1, n - 1));
        G1[vi[i]].push_back(ui[i]), G2[ui[i]].push_back(vi[i]);
    }
    for (ull i = 0; i < n; i++)
    {
        sort(G1[i].begin(), G1[i].end()), sort(G2[i].begin(), G2[i].end());
        ull s1 = G1[i].size(), s2 = G2[i].size();
        for (ull id = 0; id < s1; id++)
        {
            ans2 += A * G1[i][id] * (s1 - 1 - id + s2);
            ans2 += B * (G1[i][id] * id + i * s2);
            ans2 += C * i * id;
        }
        for (ull id = 0; id < s2; id++)
        {
            ans2 += A * i * (s2 - 1 - id);
            ans2 += B * G2[i][id] * (s2 - 1 - id);
            ans2 += C * G2[i][id] * (id + s1);
        }
    }
    for (ull i = 1; i <= m; i++)
    {
        if (deg[ui[i]] < deg[vi[i]] || (deg[ui[i]] == deg[vi[i]] && ui[i] > vi[i]))
            swap(ui[i], vi[i]);
        addpath(ui[i], vi[i]);
    }
    for (ull u = 0; u < n; u++)
    {
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            vis[edges[i].to] = true;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            for (int e = head[edges[i].to]; e != -1; e = edges[e].nxt)
                if (vis[edges[e].to])
                {
                    static ull batch[3];
                    batch[0] = u, batch[1] = edges[i].to, batch[2] = edges[e].to;
                    sort(batch, batch + 3);
                    ans3 += A * batch[0] + B * batch[1] + C * batch[2];
                }
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            vis[edges[i].to] = false;
    }
    printf("%llu\n", ans0 - ans1 + ans2 - ans3);
    return 0;
}