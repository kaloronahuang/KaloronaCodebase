// CF1322B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4e5 + 200;

int n, ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    int ans = 0;
    for (int bit = 25; bit >= 0; bit--)
    {
        int b = (1 << bit), x = 0;
        sort(ai + 1, ai + 1 + n);
        for (int i = 1; i <= n; i++)
        {
            if ((b <= (ai[i] << 1) && ai[i] < b) || (ai[i] << 1) >= (b * 3))
                x--;
            x += n - (lower_bound(ai + 1, ai + 1 + n, max(b - ai[i], 0)) - ai - 1) +
                 (lower_bound(ai + 1, ai + 1 + n, max(2 * b - ai[i], 0)) - ai - 1) -
                 (lower_bound(ai + 1, ai + 1 + n, max(3 * b - ai[i], 0)) - ai - 1);
        }
        x >>= 1;
        if (x & 1)
            ans |= b;
        for (int i = 1; i <= n; i++)
            ai[i] &= (b - 1);
    }
    printf("%d\n", ans);
    return 0;
}