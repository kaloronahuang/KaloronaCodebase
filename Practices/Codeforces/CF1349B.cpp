// CF1349B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, k, ai[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &k);
        bool flag = false;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), flag |= ai[i] == k;
        if (!flag)
        {
            puts("no");
            continue;
        }
        if (n == 1)
        {
            puts("yes");
            continue;
        }
        flag = false;
        for (int i = 1; i <= n; i++)
            flag |= (i >= 2 && ai[i - 1] >= k && ai[i] >= k) || (i >= 3 && ai[i] >= k && ai[i - 2] >= k);
        puts(flag ? "yes" : "no");
    }
    return 0;
}