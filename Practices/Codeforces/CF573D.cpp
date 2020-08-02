// CF573D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MAX_N = 3e4 + 200;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q, posa[MAX_N], posb[MAX_N], ban[MAX_N];
ll dp[MAX_N], util[MAX_N][3];
pii persons[MAX_N], horses[MAX_N];

void update(int i)
{
    util[i][0] = util[i][1] = util[i][2] = -INF;
    if (i >= 1 && ban[i] != i)
        util[i][0] = 1LL * persons[i].first * horses[i].first;
    if (i >= 2 && ban[i] != i - 1 && ban[i - 1] != i)
        util[i][1] = 1LL * persons[i].first * horses[i - 1].first + 1LL * persons[i - 1].first * horses[i].first;
    if (i >= 3)
    {
        if (ban[i] != i - 2 && ban[i - 1] != i && ban[i - 2] != i - 1)
            util[i][2] = 1LL * persons[i].first * horses[i - 2].first + 1LL * persons[i - 1].first * horses[i].first + 1LL * persons[i - 2].first * horses[i - 1].first;
        if (ban[i] != i - 1 && ban[i - 1] != i - 2 && ban[i - 2] != i)
            util[i][2] = max(util[i][2], 1LL * persons[i].first * horses[i - 1].first + 1LL * persons[i - 1].first * horses[i - 2].first + 1LL * persons[i - 2].first * horses[i].first);
    }
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &persons[i].first), persons[i].second = i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &horses[i].first), horses[i].second = i;
    sort(persons + 1, persons + 1 + n), sort(horses + 1, horses + 1 + n);
    for (int i = 1; i <= n; i++)
        posa[persons[i].second] = posb[horses[i].second] = i;
    for (int i = 1; i <= n; i++)
        ban[i] = posb[persons[i].second];
    for (int i = 1; i <= n; i++)
        update(i);
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y), x = posa[x], y = posa[y];
        swap(ban[x], ban[y]), dp[0] = 0;
        for (int i = max(1, x - 5); i <= min(x + 5, n); i++)
            update(i);
        for (int i = max(1, y - 5); i <= min(y + 5, n); i++)
            update(i);
        for (int i = 1; i <= n; i++)
        {
            dp[i] = dp[i - 1] + util[i][0];
            if (i >= 2)
                dp[i] = max(dp[i], dp[i - 2] + util[i][1]);
            if (i >= 3)
                dp[i] = max(dp[i], dp[i - 3] + util[i][2]);
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}