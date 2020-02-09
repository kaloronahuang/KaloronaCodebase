// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

int h[MAX_N], n;
long long ai[MAX_N];

// h is the hash table.

void add_fish(long long &cnt, long long x, long long len)
{
    long long y = x % len;
    while (h[y] != -1 && h[y] != x)
        y = (y + 1) % len, cnt++;
    h[y] = x;
}

long long solve(long long len)
{
    for (int i = 0; i < len; i++)
        h[i] = -1;
    long long cnt = 0;
    for (int i = 1; i <= n; i++)
        add_fish(cnt, ai[i], len);
    return cnt;
}

int main()
{
    freopen("hash.in", "r", stdin);
    freopen("hash.out", "w", stdout);
    int typ;
    scanf("%d%d", &typ, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    printf("%lld\n", solve(n));
    return 0;
}