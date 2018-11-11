#include <cstdio>
#include <algorithm>
#define Q 30000
#define N 1100000
#define inf 0x3f3f3f3f
using namespace std;
inline char gc()
{
    static char now[1 << 16], *T, *S;
    if (T == S)
    {
        T = (S = now) + fread(now, 1, 1 << 16, stdin);
        if (T == S)
            return EOF;
    }
    return *S++;
}
/*
inline int read()
{
    int x = 0;
    char ch = gc();
    while (ch < '0' || ch > '9')
        ch = gc();
    while (ch <= '9' && ch >= '0')
    {
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x;
}
*/

int read()
{
    int num;
    scanf("%d", &num);
    return num;
}

struct node
{
    int l, r, v;
} data[Q], data1[Q];
inline bool cmp(node a, node b)
{
    if (a.v > b.v)
        return true;
    else if (a.v < b.v)
        return false;
    return a.l < b.l;
}
int fa[N], n;
inline int find(int x)
{
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}
inline bool check(int x)
{
    int l = 0, r = inf;
    int l1 = inf, r1 = 0;
    for (int i = 1; i <= n + 1; ++i)
        fa[i] = i;
    for (int i = 1; i <= x; ++i)
        data[i] = data1[i];
    sort(data + 1, data + x + 1, cmp);
    int last_v = data[1].v;
    l = l1 = data[1].l;
    r = r1 = data[1].r;
    for (int i = 2; i <= x; ++i)
    {
        if (last_v != data[i].v)
        {
            int x = find(l);
            if (x <= r)
            {
                int now = find(l1);
                while (now <= r1)
                    fa[now] = fa[now + 1], now = find(now + 1);
            }
            else
                return false;
            last_v = data[i].v;
            l = l1 = data[i].l;
            r = r1 = data[i].r;
        }
        else
        {
            l = max(l, data[i].l);
            r = min(r, data[i].r);
            l1 = min(l1, data[i].l);
            r1 = max(r1, data[i].r);
            if (l > r)
                return false;
        };
    }
    if (find(l) > r)
        return false;
    return true;
}
int l, r, q;
int main()
{
    //freopen("bzoj1594.in","r",stdin);
    n = read();
    q = read();
    for (int i = 1; i <= q; ++i)
        data1[i].l = read(), data1[i].r = read(), data1[i].v = read();
    l = 0;
    r = q;
    while (l <= r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    if (l > q)
        printf("0");
    else
        printf("%d", l);
    return 0;
}