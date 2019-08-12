// B.cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define ll long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, d, tree[MAX_N << 2];
long long min_ans = 0, max_ans = 0, minusComb = 0;

vector<ll> mapping, xlist;

template <class T>
inline T read(T &x)
{
    T data = 0;
    int w = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        data = 10 * data + ch - '0', ch = getchar();
    return x = data * w;
}

inline int lowbit(int x) { return x & -x; }

void add(int x, int d)
{
    int siz = mapping.size();
    for (; x <= siz; x += lowbit(x))
        tree[x] += d;
}

int query(int x)
{
    int ans = 0;
    for (; x; x -= lowbit(x))
        ans += tree[x];
    return ans;
}

struct point
{
    ll x, y;
    bool operator<(const point &pt) const { return x < pt.x || (x == pt.x && y < pt.y); }
} pts1[MAX_N], pts2[MAX_N];

struct quad
{
    ll x, y, aff;
    bool operator<(const quad &qd) const { return x < qd.x; }
};
vector<quad> vec;

int cover[MAX_N];

int ripe(ll x) { return lower_bound(mapping.begin(), mapping.end(), x) - mapping.begin() + 1; }

void solve()
{
    memset(tree, 0, sizeof(tree));
    vec.clear(), xlist.clear(), mapping.clear();
    for (int i = 1; i <= m; i++)
    {
        vec.push_back(quad{pts2[i].x - d, pts2[i].y, 1});
        vec.push_back(quad{pts2[i].x + d + 1, pts2[i].y, -1});

        xlist.push_back(pts2[i].x - d), xlist.push_back(pts2[i].x + d + 1);

        mapping.push_back(pts2[i].y);
    }

    for (int i = 1; i <= n; i++)
    {
        xlist.push_back(pts1[i].x);
        mapping.push_back(pts1[i].y - d - 1), mapping.push_back(pts1[i].y + d);
    }

    sort(xlist.begin(), xlist.end()), sort(mapping.begin(), mapping.end());
    xlist.erase(unique(xlist.begin(), xlist.end()), xlist.end());
    mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());

    sort(vec.begin(), vec.end());
    int cur1 = 0, cur2 = 1;
    for (ll x : xlist)
    {
        while (cur1 < vec.size() && vec[cur1].x == x)
            add(ripe(vec[cur1].y), vec[cur1].aff), cur1++;
        while (cur2 <= n && pts1[cur2].x == x)
            cover[cur2] = query(ripe(pts1[cur2].y + d)) - query(ripe(pts1[cur2].y - d - 1)), cur2++;
    }

    sort(cover + 1, cover + 1 + n);

    for (int i = 1; i <= n; i++)
    {
        min_ans += 1LL * (n - i) * cover[i];
        max_ans += 1LL * (i - 1) * cover[i];
        minusComb += 1LL * (1LL * cover[i] * (cover[i] - 1) >> 1);
    }
}

int main()
{
    /*
    freopen("mhw.in", "r", stdin);
    freopen("mhw.out", "w", stdout);
    */
    read(n), read(m), read(d);
    for (int i = 1, x, y; i <= n; i++)
    {
        read(x), read(y);
        pts1[i].x = x + y, pts1[i].y = x - y;
    }
    for (int i = 1, x, y; i <= m; i++)
    {
        read(x), read(y);
        pts2[i].x = x + y, pts2[i].y = x - y;
    }
    sort(pts1 + 1, pts1 + 1 + n);
    sort(pts2 + 1, pts2 + 1 + m);

    solve();
    swap(n, m), swap(pts1, pts2);

    solve();

    printf("%lld %lld", min_ans - minusComb, max_ans - minusComb);
    return 0;
}