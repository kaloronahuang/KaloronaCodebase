// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, INF = 0x3f3f3f3f;

inline char getcha()
{
    static char buf[1 << 20], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}
void read(int &res)
{
    char ch = getcha();
    res = 0;
    while (!isdigit(ch))
        ch = getcha();
    while (isdigit(ch))
        res = (res << 3) + (res << 1) + (ch ^ 48), ch = getcha();
}

struct query
{
    int l, r, val;
    bool operator<(const query &q) const { return val > q.val || (val == q.val && l < q.l); }
} queries[MAX_N], tmp[MAX_N];

int fa[MAX_N], n, k;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

bool check(int mid)
{
    int l = 0, r = INF, l1 = INF, r1 = 0;
    for (int i = 1; i <= n + 1; i++)
        fa[i] = i;
    for (int i = 1; i <= mid; i++)
        tmp[i] = queries[i];
    sort(tmp + 1, tmp + 1 + mid);
    int last_val = tmp[1].val;
    l = l1 = tmp[1].l, r = r1 = tmp[1].r;
    for (int i = 2; i <= mid; i++)
        if (last_val != tmp[i].val)
        {
            int u = find(l);
            if (u <= r)
            {
                int now = find(l1);
                while (now <= r1)
                    fa[now] = fa[now + 1], now = find(now + 1);
            }
            else
                return false;
            last_val = tmp[i].val, l = l1 = tmp[i].l, r = r1 = tmp[i].r;
        }
        else
        {
            l = max(l, tmp[i].l), r = min(r, tmp[i].r), l1 = min(l1, tmp[i].l), r1 = max(r1, tmp[i].r);
            if (l > r)
                return false;
        }
    return find(l) <= r;
}

int main()
{
    read(n), read(k);
    for (int i = 1; i <= k; i++)
        read(queries[i].l), read(queries[i].r), read(queries[i].val);
    int l = 0, r = k;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d\n", min(k + 1, l));
    return 0;
}