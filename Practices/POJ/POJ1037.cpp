// POJ1037.cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
ll n, m, T, f[25][25][2];
bool vis[25];
void initialize()
{
    f[1][1][0] = f[1][1][1] = 1;
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= i; j++)
        {
            for (int k = j; k <= i - 1; k++)
                f[i][j][0] += f[i - 1][k][1];
            for (int k = 1; k <= j - 1; k++)
                f[i][j][1] += f[i - 1][k][0];
        }
}
int main()
{
    scanf("%d", &T);
    initialize();
    while (T--)
    {
        memset(vis, 0, sizeof(vis));
        scanf("%lld%lld", &n, &m);
        // to determine the first condition;
        ll last, k;
        for (int j = 1; j <= n; j++)
        {
            if (f[n][j][1] >= m)
            {
                last = j, k = 1;
                break;
            }
            else
                m -= f[n][j][1];
            if (f[n][j][0] >= m)
            {
                last = j, k = 0;
                break;
            }
            else
                m -= f[n][j][0];
        }
        vis[last] = true;
        printf("%lld", last);
        for (int i = 2; i <= n; i++)
        {
            k ^= 1;
            int j = 0;
            for (int len = 1; len <= n; len++)
            {
                if (vis[len])
                    continue;
                j++;
                if ((k == 1 && len > last) || (k == 0 && len < last))
                    if (f[n - i + 1][j][k] >= m)
                    {
                        last = len;
                        break;
                    }
                    else
                        m -= f[n - i + 1][j][k];
            }
            printf(" %lld", last);
            vis[last] = true;
        }
        puts("");
    }
    return 0;
}