// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1010, RANGE = 3e5 + 20000;
int ai[MAX_N], cnt[RANGE], n, ans;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            cnt[ai[i] + ai[j]]++;
    for (int i = 0; i < RANGE; i++)
        ans = max(cnt[i], ans);
    printf("%d", ans);
    return 0;
}