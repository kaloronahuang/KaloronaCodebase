// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int ai[MAX_N], bi[MAX_N], n, m;

namespace IO
{
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                                 \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
         ? EOF                                                               \
         : *p1++)
inline int rd()
{
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (isdigit(c))
        x = x * 10 + (c ^ 48), c = gc();
    return x * f;
}
char pbuf[1 << 20], *pp = pbuf;
inline void push(const char &c)
{
    if (pp - pbuf == 1 << 20)
        fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
    *pp++ = c;
}
inline void write(int x)
{
    static int sta[35];
    int top = 0;
    do
    {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        push(sta[--top] + '0');
}
} // namespace IO

inline void solve(int l1, int r1, int l2, int r2, int k)
{
    if (k == 1)
    {
        if (l1 > r1)
            printf("%d\n", bi[l2]);
        else if (l2 > r2)
            printf("%d\n", ai[l1]);
        else
            printf("%d\n", min(ai[l1], bi[l2]));
        return;
    }
    int s = l1 + (k >> 1) - 1, t = l2 + (k >> 1) - 1;
    if (s > r1)
        s = n + 1;
    if (t > r2)
        t = n + 1;
    if (ai[s] > bi[t])
        solve(l1, r1, l2 + (k >> 1), r2, k - (k >> 1));
    else
        solve(l1 + (k >> 1), r1, l2, r2, k - (k >> 1));
}

using namespace IO;

int main()
{
	freopen("median.in", "r", stdin);
	freopen("median.out", "w", stdout);
    n = rd(), m = rd();
    // scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++)
        // scanf("%d", &ai[i]);
        ai[i] = rd();
    for (int i = 1; i <= n; i++)
        // scanf("%d", &bi[i]);
        bi[i] = rd();
    ai[n + 1] = bi[n + 1] = 0x3f3f3f3f;
    while (m--)
    {
        int opt, x, y, z, l1, l2, r1, r2;
        // scanf("%d", &opt);
        opt = rd();
        if (opt == 1)
            x = rd(), y = rd(), z = rd(), ((x == 0) ? ai[y] : bi[y]) = z;
        else
            l1 = rd(), r1 = rd(), l2 = rd(), r2 = rd(), solve(l1, r1, l2, r2, (((r1 - l1 + 1) + (r2 - l2 + 1)) >> 1) + 1);
    }
    return 0;
}