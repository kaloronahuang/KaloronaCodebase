// FOJ6765.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20;

int n, m, ai[MAX_N];

int main()
{
    freopen("lock.in", "r", stdin), freopen("lock.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &ai[i]);
    int ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
    {
        long long sum = 0;
        int min_val = 0x3f3f3f3f;
        for (int i = 0; i < n; i++)
            if (stat & (1 << i))
                sum += ai[i];
            else
                min_val = min(min_val, ai[i]);
        if (sum < m && 0LL + sum + min_val >= m)
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}