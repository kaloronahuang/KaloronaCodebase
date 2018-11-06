// P2339.cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int maxc = 1010;
const int maxt = 22000;
const int INF = 0x7fffffff;
int C, H, B;
struct teacher
{
    int X, T, id;
    bool operator<(const teacher &t) const
    {
        return T < t.T;
    }
} ts[maxc];

// dp[hw][pos] = max(dp[hw-1][pos-<every before>] + timecost)
int dp[maxc][maxt];

void solve()
{
}

int main()
{
    cin >> C >> H >> B;
    for (int i = 1; i <= C; i++)
    {
        int x, t;
        cin >> x >> t;
        ts[i] = teacher{x, t, i};
    }
    sort(ts + 1, ts + C + 1);
    solve();
    return 0;
}