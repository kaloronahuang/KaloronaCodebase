// U65320.cpp
#include <bits/stdc++.h>
#define pr pair<ll, ll>
typedef long long ll;

using namespace std;

const int MAX_N = 1e5 + 200;

ll dp[MAX_N], n, m, tmp[MAX_N];

struct category
{
    bool toggle = false;
    pr main_key;
    vector<pr> pieces;

    void process()
    {
        memset(tmp, 0, sizeof(tmp));
        for (int j = n; j >= 0; j--)
            if (j >= main_key.first)
                tmp[j] = dp[j - main_key.first] + main_key.second;
        for (pr now : pieces)
            for (int i = n; i >= 0; i--)
                if (i >= now.first + main_key.first)
                    tmp[i] = max(tmp[i], tmp[i - now.first] + 1LL * now.second);
    }
} cates[1010];

int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1, a, b, c; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        if (c == 0)
            cates[i].main_key = make_pair(a, 1LL * a * b), cates[i].toggle = true;
        else
            cates[c].pieces.push_back(make_pair(a, 1LL * a * b)), cates[c].toggle = true;
    }
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++)
        if (cates[i].toggle == true)
        {
            cates[i].process();
            for (int i = 0; i <= n; i++)
                dp[i] = max(dp[i], tmp[i]);
        }
    printf("%lld", dp[n]);
    return 0;
}