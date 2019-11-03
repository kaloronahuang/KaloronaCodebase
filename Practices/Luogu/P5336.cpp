// P5336.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 55;

ll n, a, b, wi[MAX_N], f[MAX_N][MAX_N][MAX_N][MAX_N], g[MAX_N][MAX_N];
vector<ll> vec;

ll pow2(ll bas) { return bas * bas; }

int main()
{
    scanf("%lld%lld%lld", &n, &a, &b);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &wi[i]), vec.push_back(wi[i]);
    memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    ll upper = vec.size();
    for (int i = 1; i <= n; i++)
    {
        wi[i] = lower_bound(vec.begin(), vec.end(), wi[i]) - vec.begin() + 1;
        f[i][i][wi[i]][wi[i]] = 0, g[i][i] = a;
    }
    for (int len = 2; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for (ll low = 1; low <= upper; low++)
                for (ll high = low; high <= upper; high++)
                {
                    f[i][j][min(low, wi[j])][max(high, wi[j])] = min(f[i][j][min(low, wi[j])][max(high, wi[j])], f[i][j - 1][low][high]);
                    for (int midpt = i; midpt < j; midpt++)
                        f[i][j][low][high] = min(f[i][j][low][high], f[i][midpt][low][high] + g[midpt + 1][j]);
                }
            for (ll low = 1; low <= n; low++)
                for (ll high = low; high <= n; high++)
                    g[i][j] = min(g[i][j], f[i][j][low][high] + a + b * pow2(vec[high - 1] - vec[low - 1]));
        }
    printf("%lld", g[1][n]);
    return 0;
}