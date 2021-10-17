// I.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7, dishes[] = {7, 27, 41, 49, 63, 78, 108};

int T, n, ai[MAX_N], sum[3];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &ai[i]), ai[i]--;
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans += dishes[ai[i]];
        if (ans >= 120)
            ans -= 50;
        else if (ans >= 89)
            ans -= 30;
        else if (ans >= 69)
            ans -= 15;
        printf("%d\n", ans);
    }
    return 0;
}