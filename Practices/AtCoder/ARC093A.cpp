// ARC093A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ai[MAX_N];

int main()
{
    scanf("%d", &n), n += 2;
    for (int i = 2; i <= n - 1; i++)
        scanf("%d", &ai[i]);
    int ans = 0;
    for (int i = 2; i <= n; i++)
        ans += abs(ai[i] - ai[i - 1]);
    for (int i = 2; i < n; i++)
    {
        ans -= abs(ai[i - 1] - ai[i]) + abs(ai[i + 1] - ai[i]) - abs(ai[i + 1] - ai[i - 1]);
        printf("%d\n", ans);
        ans += abs(ai[i - 1] - ai[i]) + abs(ai[i + 1] - ai[i]) - abs(ai[i + 1] - ai[i - 1]);
    }
    return 0;
}