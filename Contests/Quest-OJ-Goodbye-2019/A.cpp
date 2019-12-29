// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, cnt[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), cnt[u]++, cnt[v]++;
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, cnt[i] + 1);
    printf("%d\n", ans);
    return 0;
}