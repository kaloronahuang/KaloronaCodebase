// P2898.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000020;
const int INF = 1e9 + 1e8;
int n, q, mem[maxn];
struct RMQ
{
    int left, right, exp;
} seq[maxn], tmp[maxn];

bool cmp(RMQ r1, RMQ r2)
{
    if (r1.exp == r2.exp)
        return r1.left < r2.left;
    return r1.exp > r2.exp;
}

int find(int x)
{
    return (mem[x] == x) ? mem[x] : mem[x] = find(mem[x]);
}

bool check(int val)
{
    int l1 = 0, r1 = INF, l2 = INF, r2 = 0;
    // initialize the mem[]
    for (int i = 0; i <= n + 1; i++)
        mem[i] = i;
    for (int i = 1; i <= val; i++)
        tmp[i] = seq[i];
    sort(tmp + 1, tmp + 1 + val, cmp);
    int lval = tmp[1].exp;
    l1 = l2 = tmp[1].left, r1 = r2 = tmp[1].right;
    for (int i = 2; i <= val; i++)
        if (tmp[i].exp != lval)
        {
            int now = find(l2);
            if (find(l1) <= r1)
                while (now <= r2)
                    mem[now] = mem[now + 1], now = find(now + 1);
            else
                return false;
            lval = tmp[i].exp;
            l1 = l2 = tmp[i].left;
            r1 = r2 = tmp[i].right;
        }
        else
        {
            l1 = max(l1, tmp[i].left), r1 = min(r1, tmp[i].right);
            l2 = min(l2, tmp[i].left), r2 = max(r2, tmp[i].right);
            lval = tmp[i].exp;
            if (l1 > r1)
                return false;
        }
    if (find(l1) > r1)
        return false;
    return true;
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d%d", &seq[i].left, &seq[i].right, &seq[i].exp);
    int l = 0;
    int r = q;
    while (l <= r)
    {
        int mid = ((l + r) >> 1);
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