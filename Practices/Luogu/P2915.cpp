// P2915.cpp
#include <iostream>
#include <cmath>
using namespace std;

#define ll unsigned long long
const int maxn = 16;
ll dp[1 << maxn][maxn];
int n, k, nowState;
int seq[maxn];

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> seq[i];
    for (int cowId = 0; cowId < n; cowId++)
        dp[1 << cowId][cowId] = 1;
    for (int lastState = 0; lastState < (1 << n); lastState++)
        for (int lastCow = 0; lastCow < n; lastCow++)
            if (lastState & (1 << lastCow))
                for (int nowCow = 0; nowCow < n; nowCow++)
                    if (!(lastState & (1 << nowCow)) && abs(seq[nowCow] - seq[lastCow]) > k)
                        nowState = lastState | (1 << nowCow),
                        dp[nowState][nowCow] += dp[lastState][lastCow];
    ll ans = 0;
    for (int i = 0; i < n; i++)
        ans += dp[(1 << n) - 1][i];
    cout << ans;
    return 0;
}