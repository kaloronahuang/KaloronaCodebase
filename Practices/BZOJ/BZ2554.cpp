// BZ2554.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200;

int n, cnt[26];
char str[MAX_N];
double ai[MAX_N], bi[MAX_N], f[MAX_N], g[MAX_N], ans;

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        cnt[str[i] - 'A']++;
    for (int i = 1; i <= n; i++)
        g[i] = 1.0 * i / n;
    ai[1] = 1, bi[1] = 0;
    for (int i = 1; i < n; i++)
    {
        ai[i + 1] = (ai[i] - ai[i - 1] * (i - 1) / (2 * i)) * (2 * i) / (i + 1);
        bi[i + 1] = (bi[i] - bi[i - 1] * (i - 1) / (2 * i) - double(n * (n - 1)) / double(2 * i * (n - i))) * (2 * i) / (i + 1);
    }
    f[1] = -bi[n] / ai[n];
    for (int i = 0; i < 26; i++)
        ans += g[cnt[i]] * (ai[cnt[i]] * f[1] + bi[cnt[i]]);
    printf("%.1lf\n", ans);
    return 0;
}