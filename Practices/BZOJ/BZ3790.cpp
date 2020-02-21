// BZ3790.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, match[MAX_N], len, stot, ans, nodes[MAX_N];
char org[MAX_N], str[MAX_N];

struct seg
{
    int l, r;
    bool operator<(const seg &rhs) const { return r < rhs.r || (r == rhs.r && l < rhs.l); }
} segs[MAX_N << 1];

inline int lowbit(int x) { return x & (-x); }

int query(int x, int ret = 0x3f3f3f3f)
{
    ret = nodes[x];
    for (; x && x <= n; x += lowbit(x))
        ret = min(ret, nodes[x]);
    return ret;
}

void update(int x, int d)
{
    for (; x; x -= lowbit(x))
        nodes[x] = min(nodes[x], d);
}

int main()
{
    while (scanf("%s", org + 1) != EOF)
    {
        memset(nodes, 0x3f, sizeof(nodes)), nodes[0] = 0;
        len = 0, n = strlen(org + 1), stot = 0, ans = 0x3f3f3f3f;
        // manacher;
        str[++len] = '?';
        for (int i = 1; i <= n; i++)
            str[++len] = '#', str[++len] = org[i];
        str[++len] = '#', str[++len] = '!';
        int ptr = 0, rig = 0;
        for (int i = 1; i <= len; i++)
        {
            if (i < rig)
                match[i] = min(rig - i, match[(ptr << 1) - i]);
            else
                match[i] = 1;
            while (str[i - match[i]] == str[i + match[i]])
                match[i]++;
            if (((i - match[i] + 2) >> 1) <= ((i + match[i] - 2) >> 1))
                segs[++stot] = seg{(i - match[i] + 2) >> 1, (i + match[i] - 2) >> 1};
            if (i + match[i] > rig)
                rig = i + match[i], ptr = i;
        }
        sort(segs + 1, segs + 1 + stot);
        for (int i = 1; i <= stot; i++)
        {
            int dp = query(segs[i].l - 1) + 1;
            if (segs[i].r == n)
                ans = min(ans, dp);
            update(segs[i].r, dp);
        }
        printf("%d\n", ans - 1);
    }
    return 0;
}