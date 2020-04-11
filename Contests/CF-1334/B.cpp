// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, ai[MAX_N], x;
double tmp[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &x);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        sort(ai + 1, ai + 1 + n);
        long long ans = 0;
        for (int i = n; i >= 0; i--)
        {
            ans += ai[i];
            if (double(ans) / double(n - i + 1) < x || i == 0)
            {
                printf("%d\n", n - i);
                break;
            }
        }
    }
    return 0;
}