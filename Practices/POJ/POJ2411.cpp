// POJ2411.cpp
#include <cstdio>
#define ll long long
using namespace std;
const int MAX_N = 12, RANGE = (1 << MAX_N);
ll dp[MAX_N][RANGE], n, m;
bool valid[RANGE];
int main()
{
    while (scanf("%lld%lld", &n, &m) && n != 0 && m != 0)
    {
        for (int i = 0; i < (1 << m); i++)
        {
            int cnt = 0, odd = 0;
            for (int j = 0; j < m; j++)
                if ((i >> j) & 1)
                    odd |= cnt, cnt = 0;
                else
                    cnt ^= 1;
            valid[i] = cnt | odd ? 0 : 1;
        }
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < (1 << m); j++)
            {
                dp[i][j] = 0;
                for (int k = 0; k < (1 << m); k++)
                    if ((j & k) == 0 && (valid[j | k]))
                        dp[i][j] += dp[i - 1][k];
            }
        printf("%lld\n", dp[n][0]);
    }
    return 0;
}