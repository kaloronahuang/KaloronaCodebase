// P2148.cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T, x, y, acc, n, cnt;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n), acc = 0;
        for (int i = 1, pans = 0; i <= n; i += 2)
        {
            scanf("%d%d", &x, &y), pans = (x - 1) | (y - 1), cnt = 0;
            while (pans & 1)
                cnt++, pans >>= 1;
            acc ^= cnt;
        }
        puts(acc ? "YES" : "NO");
    }
    return 0;
}