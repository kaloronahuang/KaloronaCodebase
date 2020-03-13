// CF1053A.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    bool flag = k % 2 == 0;
    if (k % 2 == 0)
        k /= 2;
    if (1LL * n * m % k != 0)
        puts("NO");
    else
    {
        puts("YES");
        int x = n, y = m;

        int dx = __gcd(x, k);
        x /= dx, k /= dx;
        int dy = __gcd(y, k);
        y /= dy, k /= dy;
        if (!flag)
            if (x * 2 <= n)
                x *= 2;
            else if (y * 2 <= m)
                y *= 2;
        puts("0 0"), printf("%d %d\n", 0, y), printf("%d %d\n", x, 0);
    }

    return 0;
}