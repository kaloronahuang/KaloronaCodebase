// P4380.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 255;

int n, mat[MAX_N][MAX_N], mem[MAX_N * MAX_N], siz[MAX_N * MAX_N], ntot, psiz[MAX_N * MAX_N];
bool appear[MAX_N * MAX_N];

struct node
{
    int x, y, colx, coly;
    bool operator<(const node &rhs) const { return colx < rhs.colx || (colx == rhs.colx && coly < rhs.coly); }
} nodes[MAX_N * MAX_N * MAX_N];

int getId(int x, int y) { return (x - 1) * n + y; }

bool check(int x, int y) { return x <= n && x >= 1 && y <= n && y >= 1; }

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void newNode(int x, int y, int colx, int coly)
{
    if (colx > coly)
        swap(x, y), swap(colx, coly);
    nodes[++ntot] = node{x, y, colx, coly};
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]), mem[getId(i, j)] = getId(i, j);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (check(i - 1, j) && mat[i][j] == mat[i - 1][j] && find(getId(i, j)) != find(getId(i - 1, j)))
                mem[find(getId(i, j))] = find(getId(i - 1, j));
            if (check(i, j - 1) && mat[i][j] == mat[i][j - 1] && find(getId(i, j)) != find(getId(i, j - 1)))
                mem[find(getId(i, j))] = find(getId(i, j - 1));
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            siz[find(getId(i, j))]++;
    int ans1 = 0, ans2 = 0;
    memcpy(psiz, siz, sizeof(siz));
    for (int i = 1; i <= n * n; i++)
        ans1 = max(ans1, siz[i]);
    printf("%d\n", ans1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (check(i - 1, j) && mat[i][j] != mat[i - 1][j])
                newNode(find(getId(i, j)), find(getId(i - 1, j)), mat[i][j], mat[i - 1][j]);
            if (check(i, j - 1) && mat[i][j] != mat[i][j - 1])
                newNode(find(getId(i, j)), find(getId(i, j - 1)), mat[i][j], mat[i][j - 1]);
        }
    sort(nodes + 1, nodes + 1 + ntot);
    for (int i = 1; i <= ntot; i++)
    {
        vector<int> idx;
        idx.push_back(nodes[i].x), idx.push_back(nodes[i].y);
        appear[nodes[i].x] = appear[nodes[i].y] = true;
        if (find(nodes[i].x) != find(nodes[i].y))
        {
            psiz[find(nodes[i].y)] += psiz[find(nodes[i].x)];
            mem[find(nodes[i].x)] = find(nodes[i].y);
        }
        while (i + 1 <= ntot && nodes[i + 1].colx == nodes[i].colx && nodes[i + 1].coly == nodes[i].coly)
        {
            i++;
            if (!appear[nodes[i].x])
                appear[nodes[i].x] = true, idx.push_back(nodes[i].x);
            if (!appear[nodes[i].y])
                appear[nodes[i].y] = true, idx.push_back(nodes[i].y);
            if (find(nodes[i].x) != find(nodes[i].y))
            {
                psiz[find(nodes[i].y)] += psiz[find(nodes[i].x)];
                mem[find(nodes[i].x)] = find(nodes[i].y);
            }
        }
        for (int i = 0, siz_ = idx.size(); i < siz_; i++)
            ans2 = max(ans2, psiz[idx[i]]);
        for (int i = 0, siz_ = idx.size(); i < siz_; i++)
            mem[idx[i]] = idx[i], psiz[idx[i]] = siz[idx[i]], appear[idx[i]] = false;
    }
    printf("%d\n", ans2);
    return 0;
}