// P1351.cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define ull unsigned long long
const int maxn = 2000000;
int n;
ull W[maxn];
// The graph data structure;
int to[maxn];
int point[maxn];
int next[maxn];
bool vis[maxn];
int current = 0;
// answers;
ull ans_max = 0;
ull ans_tot = 0;
// initialize to make the graph up;
void init()
{
    memset(to, -1, sizeof(to));
    memset(point, -1, sizeof(point));
    memset(next, -1, sizeof(next));
    memset(vis, false, sizeof(vis));
    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        next[current] = point[x];
        to[current] = y;
        point[x] = current;
        current++;
        next[current] = point[y];
        to[current] = x;
        point[y] = current;
        current++;
    }
    for (int i = 1; i <= n; i++)
        cin >> W[i];
}
// calculate the n^2;
ull secondary(ull a)
{
    return a * a;
}
// solve;
void solve()
{
    for (int i = 1; i <= n; i++)
    {
        // get the maximum and the second one;
        ull firmax = 0;
        ull secmax = 0;
        // the term1 and the term2;
        ull tmp1 = 0;
        ull tmp2 = 0;
        for (int j = point[i]; j != -1; j = next[j])
        {
            int jto = to[j];
            if (W[jto] > firmax)
                secmax = firmax, firmax = W[jto];
            else if (W[jto] > secmax)
                secmax = W[jto];
            tmp1 += W[jto];
            tmp2 += secondary(W[jto]);
        }
        // add them up;
        ans_tot += (secondary(tmp1) - tmp2) % 10007;
        ans_tot %= 10007;
        ans_max = max(ans_max, firmax * secmax);
    }
}
// just solve it;
int main()
{
    init();
    solve();
    cout << ans_max << " " << ans_tot;
    return 0;
}