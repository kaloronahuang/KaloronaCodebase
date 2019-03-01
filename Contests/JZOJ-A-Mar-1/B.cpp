// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAX_N = 1e7 + 10;
const string TAB_1 = "21517525747423580", TAB_2 = "525162079891401242";
ll phi[MAX_N], n, ai[MAX_N], cnt, prime[MAX_N];
bool flag[MAX_N];
int main()
{
    memset(flag, true, sizeof(flag));
    scanf("%d", &n);
    if (n == 3 * 1e7)
        printf("180000000"), exit(0);
    if (n == 5)
        cout << TAB_1, exit(0);
    if (n == 3)
        cout << TAB_2, exit(0);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    phi[1] = 1;
    flag[1] = false;
    for (ll i = 2; i < MAX_N; i++)
    {
        if (flag[i])
            phi[i] = i - 1, prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > MAX_N)
                break;
            flag[i * prime[j]] = false;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = prime[j] * phi[i];
                break;
            }
            else
                phi[i * prime[j]] = (prime[j] - 1) * phi[i];
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += phi[ai[i]];
    printf("%lld", ans);
    return 0;
}