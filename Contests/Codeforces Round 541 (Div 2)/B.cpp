// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e4 + 200;
int n, ai[MAX_N], bi[MAX_N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]);
    long long ans = 0;
    int lst = 0;
    for (int i = 1; i <= n; i++)
    {
        if (min(ai[i], bi[i]) >= lst)
            ans += min(ai[i], bi[i]) - lst + 1, lst = max(lst, min(ai[i], bi[i]) + 1);
        lst = max(lst, max(ai[i], bi[i]));
    }
    printf("%lld", ans);
    return 0;
}