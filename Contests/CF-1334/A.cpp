// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n, pi[MAX_N], ci[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &pi[i], &ci[i]);
        bool flag = true;
        for (int i = 1; i <= n; i++)
            flag &= pi[i] >= pi[i - 1] && ci[i] >= ci[i - 1] && ci[i] - ci[i - 1] <= pi[i] - pi[i - 1];
        if (flag)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}