// BZ1101.cpp
#include <bits/stdc++.h>
#define ll int
using namespace std;
const int MAX_N = 5e4 + 200;
ll mobi[MAX_N], sum[MAX_N], n;
bool vis[MAX_N];
int main()
{
    for (int i = 1; i < MAX_N; i++)
        mobi[i] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (vis[i])
            continue;
        mobi[i] = -1;
        for (int j = 2; i * j < MAX_N; j++)
        {
            vis[i * j] = true;
            if (j % i == 0)
                mobi[i * j] = 0;
            else
                mobi[i * j] *= -1;
        }
    }
    for (int i = 1; i < MAX_N; i++)
        sum[i] = sum[i - 1] + mobi[i];
    scanf("%d", &n);
    while (n--)
    {
        int a, b, k, gx;
        scanf("%d%d%d", &a, &b, &k);
        a /= k, b /= k;
        int ans = 0;
        for (int i = 1; i <= min(a, b); i = gx + 1)
        {
            gx = min(a / (a / i), b / (b / i));
            ans += (sum[gx] - sum[i - 1]) * (a / i) * (b / i);
        }
        printf("%d\n", ans);
    }
    return 0;
}