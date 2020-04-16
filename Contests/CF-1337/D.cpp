// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int T, n[3], seq[3][MAX_N];
vector<int *> p;

ll pow2(ll bas) { return bas * bas; }

ll solve(int i, int j, int k) { return pow2(p[0][i] - p[1][j]) + pow2(p[0][i] - p[2][k]) + pow2(p[1][j] - p[2][k]); }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 0; i < 3; i++)
            scanf("%d", &n[i]);
        for (int i = 0; i < 3; i++)
            for (int j = 1; j <= n[i]; j++)
                scanf("%d", &seq[i][j]);
        seq[0][0] = n[0], seq[1][0] = n[1], seq[2][0] = n[2];
        for (int i = 0; i < 3; i++)
            sort(seq[i] + 1, seq[i] + 1 + n[i]);
        long long ans = 1LL << 62;
        p = vector<int *>{seq[0], seq[1], seq[2]};
        do
        {
            for (int i = 1; i <= p[0][0]; i++)
            {
                int mid = p[0][i];
                int lft = lower_bound(p[1] + 1, p[1] + 1 + p[1][0], mid) - p[1];
                if (lft > 1 && p[1][lft] != mid)
                    lft--;
                int rig = lower_bound(p[2] + 1, p[2] + 1 + p[2][0], mid) - p[2];
                if (lft == p[1][0] + 1 || rig == p[2][0] + 1)
                    continue;
                ans = min(ans, solve(i, lft, rig));
            }
        } while (next_permutation(p.begin(), p.end()));
        printf("%lld\n", ans);
    }
    return 0;
}