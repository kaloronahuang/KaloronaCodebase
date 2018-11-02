// P1156.cpp
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Constants;
const int maxn = 2000;
const int maxt = 20000;
const int INF = 0x7fffffff - 10;
// Data structures;
int D, G;
int dp[maxn][200];
struct garbage
{
    int t, f, h;
    // Comparing function for sorting.
    bool operator<(const garbage &g) const
    {
        return t < g.t;
    }
} gars[maxn];
// To indicate if the genDP() exit normally;
bool flag = false;

void genDP()
{
    // generate;
    for (int i = 0; i < G; i++)
        for (int j = 0; j <= D; j++)
        {
            // If cow died;
            if (dp[i][j] < 0)
                continue;
            // If the cow is able to get out;
            if (j + gars[i + 1].h >= D && dp[i][j] >= (gars[i + 1].t - gars[i].t))
            {
                cout << gars[i + 1].t;
                flag = true;
                return;
            }
            // Transform the status;
            if (dp[i][j] - (gars[i + 1].t - gars[i].t) >= 0)
                dp[i + 1][j + gars[i + 1].h] = dp[i][j] - (gars[i + 1].t - gars[i].t);
            if (dp[i][j] - (gars[i + 1].t - gars[i].t) >= 0)
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + gars[i + 1].f - (gars[i + 1].t - gars[i].t));
        }
}
// The main func;
int main()
{
    // Prep for data;
    cin >> D >> G;
    gars[0].t = gars[0].f = gars[0].h = 0;
    for (int i = 1; i <= G; i++)
        cin >> gars[i].t >> gars[i].f >> gars[i].h;
    sort(gars + 1, gars + G + 1);
    fill(dp[0], dp[0] + maxn * 200, -INF);
    // The startup value of the health is 10;
    dp[0][0] = 10;
    genDP();
    if (flag)
        return 0;
    // If the genDP() exit abnormally:
    int m = 10;
    int acc = 0;
    for (int i = 1; i <= G; i++)
    {
        if (gars[i].t - gars[i - 1].t > m)
        {
            cout << m + acc;
            return 0;
        }
        acc += gars[i].t - gars[i - 1].t;
        m -= gars[i].t - gars[i - 1].t;
        m += gars[i].f;
    }
    // output;
    cout << acc + m;
    return 0;
}