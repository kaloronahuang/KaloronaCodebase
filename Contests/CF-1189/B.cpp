// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 2000;

int n, seq[MAX_N], ans[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    sort(seq + 1, seq + 1 + n);
    ans[n] = seq[n];
    for (int i = 1; i <= n - 2; i++)
        ans[i + 1] = seq[i];
    ans[1] = seq[n - 1];
    for (int i = 2; i <= n; i++)
        if (ans[i] >= ans[i - 1] + ans[i % n + 1] || ans[1] >= ans[2] + ans[n])
            puts("NO"), exit(0);
    puts("YES");
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}