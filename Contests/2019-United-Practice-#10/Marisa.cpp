// Marisa.cpp
#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

const int MAX_N = 1010, DOM = 2e6 + 200, mod = 1e9 + 7;

int T, n, cnt[MAX_N], tot, fa[MAX_N * MAX_N];
bitset<110> nodes[MAX_N], curt;
unordered_map<bitset<110>, int> id;

int getPos(int x, int y) { return x * n + y; }

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void unite(int x, int y)
{
    if (find(x) != find(y))
        fa[find(x)] = find(y);
}

void dfs(int ln)
{
    if (ln == n)
    {
        nodes[++tot] = curt;
        id[curt] = tot;
        return;
    }
    for (int i = 0; i < n; i++)
        if (cnt[i] < 2)
            for (int j = i + 1; j < n; j++)
                if (cnt[j] < 2)
                {
                    cnt[i]++, cnt[j]++;
                    curt[getPos(ln, i)] = 1, curt[getPos(ln, j)] = 1;
                    dfs(ln + 1);
                    curt[getPos(ln, i)] = 0, curt[getPos(ln, j)] = 0;
                    cnt[i]--, cnt[j]--;
                }
}

int main()
{
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    scanf("%d", &T);
    while (T--)
    {
        id.clear();
        tot = 0, scanf("%d", &n);
        dfs(0);
        for (int i = 1; i <= tot; i++)
            fa[i] = i;
        for (int idx = 1; idx <= tot; idx++)
        {
            bitset<110> bt = nodes[idx], tmp = bt;
            // swap the line;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    int tmp = bt[getPos(i, j)];
                    bt[getPos(i, j)] = bt[getPos(((i + 1) % n), j)];
                    bt[getPos(((i + 1) % n), j)] = tmp;
                }
                unite(id[tmp], id[bt]);
                bt = tmp;
            }
            for (int j = 0; j < n; j++)
            {
                for (int i = 0; i < n; i++)
                {
                    int tmp = bt[getPos(i, j)];
                    bt[getPos(i, j)] = bt[getPos(i, (j + 1) % n)];
                    bt[getPos(i, (j + 1) % n)] = tmp;
                }
                unite(id[tmp], id[bt]);
                bt = tmp;
            }
        }
        int ans = 0;
        for (int i = 1; i <= tot; i++)
            if (find(i) == i)
                ans++;
        printf("%d\n", ans);
    }
    return 0;
}