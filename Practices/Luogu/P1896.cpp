// P1896.cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 11;
#define ll long long
int MAX;
int n, k;
bool sigLine[1 << maxn];
bool doubleLine[1 << maxn][1 << maxn];
int king[1 << maxn];
ll dp[maxn][100][1 << maxn];

int main()
{
    cin >> n >> k;
    MAX = 1 << n;
    for (int i = 0; i < MAX; i++)
    {
        // check if there are pairs of 1;
        if (i & (i >> 1))
            continue;
        // checked and set it true;
        sigLine[i] = true;
        // get the number of 1 within the state and record them;
        for (int j = 1; j <= i; j <<= 1)
            if (j & i)
                king[i]++;
    }
    // the first line;
    for (int i = 0; i < MAX; i++)
        if (sigLine[i])
            // the second line;
            for (int j = 0; j < MAX; j++)
                // check if these two are valid.
                if (sigLine[j] && !(i & j) && !(i & (j << 1)) && !(i & (j >> 1)))
                    // set!
                    doubleLine[i][j] = true;
    for (int i = 0; i <= MAX; i++)
        if (sigLine[i])
            dp[1][king[i]][i] = 1;
    for (int i = 1; i < n; i++)
        for (int poss = 0; poss < MAX; poss++)
            if (sigLine[poss])
                for (int nextLine = 0; nextLine < MAX; nextLine++)
                    if (sigLine[nextLine] && doubleLine[poss][nextLine])
                        for (int w = king[poss]; w + king[nextLine] <= k; w++)
                            dp[i + 1][w + king[nextLine]][nextLine] += dp[i][w][poss];
    ll ans = 0;
    for (int i = 0; i < MAX; i++)
        ans += dp[n][k][i];
    cout << ans;
    return 0;
}