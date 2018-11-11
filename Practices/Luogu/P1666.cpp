// P1666.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 60;
string dict[maxn];
long long n, dp[maxn], current;
bool possible[maxn][maxn];
bool isPrefix(string a, string b)
{
    if (b.length() > a.length())
        swap(a, b);
    return (a.find(b) == 0);
}
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        cin >> dict[i];
    sort(dict + 1, dict + n + 1);
    for (int i = 1; i <= n; i++)
    {
        dp[i] = 1;
        for (int j = 1; j <= n; j++)
            if (!isPrefix(dict[i], dict[j]))
                possible[i][j] = possible[j][i] = true;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            if (possible[i][j])
                dp[j] += dp[i];
    for (int i = 1; i <= n; i++)
        ans += dp[i];
    printf("%lld", ans + 1);
    return 0;
}
