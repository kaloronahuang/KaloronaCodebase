// xor.cpp
#include <bits/stdc++.h>
#define ull unsigned int

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, prefix[MAX_N][32];
ull ai[MAX_N], pre[MAX_N], nodes[MAX_N], anses[MAX_N];
unordered_map<ull, int> pos;
vector<pair<int, int> /**/> vec[MAX_N];

int lowbit(int x) { return x & (-x); }

void update(int x, ull val)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] ^= val;
}

int query(int x, ull ret = 0)
{
    for (; x; x -= lowbit(x))
        ret ^= nodes[x];
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%u", &ai[i]), pre[i] = pre[i - 1] ^ ai[i];
    scanf("%d", &m);
    for (int i = 1, l, r; i <= m; i++)
        scanf("%d%d", &l, &r), vec[r].push_back(make_pair(l, i)), anses[i] = pre[r] ^ pre[l - 1];
    ull tot = 0;
    for (int i = 1; i <= n; i++)
    {
        if (pos[ai[i]])
            update(pos[ai[i]], ai[i]);
        else
            tot ^= ai[i];
        update(pos[ai[i]] = i, ai[i]);
        for (int idx = 0, siz = vec[i].size(); idx < siz; idx++)
            anses[vec[i][idx].second] ^= tot ^ query(vec[i][idx].first - 1);
    }
    for (int i = 1; i <= m; i++)
        printf("%u\n", anses[i]);
    return 0;
}