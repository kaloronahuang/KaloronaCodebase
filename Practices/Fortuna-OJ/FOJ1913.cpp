// FOJ1913.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10100, bitnum = 133;
typedef unsigned long long ull;

int T, n, ai[MAX_N];
ull nodes[2][MAX_N], pw[MAX_N];

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
        ch = nc();
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

inline int lowbit(int x) { return x & (-x); }

void update(ull *arr, int x)
{
    for (int i = x; i <= n; i += lowbit(i))
        arr[i] += pw[i - x];
}

ull query(ull *arr, int x, ull ret = 0)
{
    for (int i = x; i; i -= lowbit(i))
        ret += arr[i] * pw[x - i];
    return ret;
}

ull query(ull *arr, int l, int r) { return query(arr, r) - query(arr, l - 1) * pw[r - l + 1]; }

int main()
{
    T = read();
    for (int i = pw[0] = 1; i < MAX_N; i++)
        pw[i] = pw[i - 1] * bitnum;
    while (T--)
    {
        memset(nodes, 0, sizeof(nodes));
        n = read();
        bool flag = false;
        for (int i = 1; i <= n; i++)
        {
            ai[i] = read();
            int len = min(ai[i] - 1, n - ai[i]);
            if (len && query(nodes[0], ai[i] - len, ai[i]) != query(nodes[1], n - ai[i] - len + 1, n - ai[i] + 1))
                flag = true;
            update(nodes[0], ai[i]), update(nodes[1], n - ai[i] + 1);
        }
        puts(flag ? "Y" : "N");
    }
    return 0;
}