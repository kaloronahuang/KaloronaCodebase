// P1879.cpp
#include <iostream>

using namespace std;

const int maxn = 13;
#define ll long long
int m, n;
int map[maxn];
bool sigLine[maxn][1 << maxn];
bool doubleLine[maxn][1 << maxn][1 << maxn];
ll dp[maxn][1 << maxn];
int p = 100000000;
int MAX;

int main()
{
    cin >> m >> n;
    MAX = 1 << n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            int val;
            cin >> val;
            map[i] = (map[i] << 1) + val;
        }
    // gen the states;
    for (int ln = 1; ln <= m; ln++)
        for (int i = 0; i <= MAX; i++)
            if (!(i & (i << 1)) && ((map[ln] | i) == map[ln]))
                sigLine[ln][i] = true;
    for (int ln = 1; ln < m; ln++)
        for (int i = 0; i <= MAX; i++)
            if (sigLine[ln][i])
                for (int j = 0; j <= MAX; j++)
                    if (sigLine[ln + 1][j] && !(i & j))
                        doubleLine[ln][i][j] = true;
    for (int line = 0; line <= MAX; line++)
        if (sigLine[1][line])
            dp[1][line] = 1;
    for (int ln = 1; ln < m; ln++)
        for (int i = 0; i <= MAX; i++)
            if (sigLine[ln][i])
                for (int j = 0; j <= MAX; j++)
                    if (sigLine[ln + 1][j] && doubleLine[ln][i][j])
                        dp[ln + 1][j] += dp[ln][i];
    ll ans = 0;
    for (int ln = 0; ln <= MAX; ln++)
        if (sigLine[m][ln])
            ans = ((ans % p) + (dp[m][ln] % p)) % p;
    cout << ans;
    return 0;
}