// CF1156D.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 2000;

int buff[2][MAX_N], siz[2][MAX_N], n;

int find(int x, int typ)
{
    if (x == buff[typ][x])
        return x;
    return (buff[typ][x] = find(buff[typ][x], typ));
}

void merge(int x, int y, int c)
{
    x = find(x, c), y = find(y, c);
    if (siz[c][x] < siz[c][y])
        swap(x, y);
    buff[c][y] = x, siz[c][x] += siz[c][y];
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        buff[0][i] = buff[1][i] = i;
        siz[0][i] = siz[1][i] = 1;
    }
    for (int i = 1, x, y, c; i <= n - 1; i++)
        scanf("%d%d%d", &x, &y, &c), merge(x, y, c);

    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (buff[0][i] == i)
            ans += 1LL * siz[0][i] * (siz[0][i] - 1);
        if (buff[1][i] == i)
            ans += 1LL * siz[1][i] * (siz[1][i] - 1);
        ans += 1LL * (siz[0][find(i, 0)] - 1) * (siz[1][find(i, 1)] - 1);
    }
    printf("%lld", ans);
    return 0;
}