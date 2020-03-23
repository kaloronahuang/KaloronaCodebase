// ARC101D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7;

typedef long long ll;

int n, m, ai[MAX_N], bi[MAX_N], nodes[MAX_N << 2], pts[MAX_N], lft[MAX_N], rig[MAX_N], pcnt;
struct node
{
    int x, y;
    bool operator<(const node &rhs) const { return x < rhs.x || (x == rhs.x && y > rhs.y); }
    bool operator==(const node &rhs) const { return x == rhs.x && y == rhs.y; }
} nds[MAX_N];
vector<int> mp;

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

inline int lowbit(int x) { return x & -x; }

void update(int x, int d)
{
    for (; x <= mp.size(); x += lowbit(x))
        nodes[x] = (0LL + nodes[x] + d) % mod;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret = (0LL + nodes[x] + ret) % mod;
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= n; i++)
        if (ai[i] >= bi[1] && ai[i] <= bi[m])
        {
            pts[++pcnt] = ai[i];
            int pos = lower_bound(bi + 1, bi + 1 + m, ai[i]) - bi;
            nds[pcnt] = node{ai[i] - bi[pos - 1], bi[pos] - ai[i]};
            mp.push_back(bi[pos] - ai[i]);
        }
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= pcnt; i++)
        nds[i].y = ripe(nds[i].y);
    sort(nds + 1, nds + 1 + pcnt), pcnt = unique(nds + 1, nds + 1 + pcnt) - nds - 1;
    int ans = 1;
    for (int i = 1; i <= pcnt; i++)
    {
        int sum = (query(nds[i].y - 1) + 1) % mod;
        ans = (0LL + sum + ans) % mod, update(nds[i].y, sum);
    }
    printf("%d\n", ans);
    return 0;
}