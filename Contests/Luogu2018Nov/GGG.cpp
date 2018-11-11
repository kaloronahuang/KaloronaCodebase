// GGG.cpp
#include <iostream>
#include <algorithm>

using namespace std;

#define ll long long
const int maxn = 2 << 2 + 10;
const int mod = 998244353;
ll n, m;
ll MAX;
int sigLine[maxn];
int dp[25][maxn];
 
void read()
{
    int state = 0;
    for (int i = 0; i < n; i++)
    {
        char curt;
        cin >> curt;
        int num = curt - '0';
        state = (state << 1) + num;
    }
    cin >> sigLine[state];
}

bool judge(int a, int b)
{
    return (a != b && ((a & b) == 0));
}

void genDP()
{
    for (int i = 1; i <= MAX; i++)
        dp[1][i] = dp[0][i] + sigLine[i];
    for (int ln = 2; ln <= n; ln++)
        for (int i = 1; i <= MAX; i++)
            for (int j = 1; j <= MAX; j++)
            {
                if (!(judge(i, j)))
                    continue;
                dp[ln][(i | j)] = ((dp[ln][(i | j)] % mod + dp[ln - 1][i] % mod) % mod + sigLine[(i | j)] % mod) % mod;
            }
}

int main()
{
    cin >> n >> m;
    MAX = (1 << n) - 1;
    for (int i = 1; i <= m; i++)
        read();
    for (int i = 0; i <= MAX; i++)
        dp[0][i] = sigLine[0];
    genDP();
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans % mod + dp[i][MAX] % mod) % mod;
    cout << ans;
    return 0;
}