// 1005.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int T, n, m, ai[MAX_N], sgn;
ll prefix[MAX_N];

ll calc(int pos) { return 1LL * pos * prefix[n] - prefix[pos] * n; }

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m), sgn = 1;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), prefix[i] = prefix[i - 1] + ai[i];
        if (prefix[n] == 0)
        {
            map<ll, int> pos;
            pos[0] = 0;
            for (int i = 1; i <= n; i++)
                if (!pos.count(prefix[i]))
                    pos[prefix[i]] = i;
            while (m--)
            {
                ll x;
                scanf("%lld", &x);
                if (pos.count(x) == 0)
                    puts("-1");
                else
                    printf("%d\n", pos[x]);
            }
        }
        else
        {
            if (prefix[n] < 0)
                sgn = -1;
            for (int i = 1; i <= n; i++)
                ai[i] *= sgn, prefix[i] = prefix[i - 1] + ai[i];
            map<ll, vector<int>> pos;
            map<ll, int> mpos;
            mpos[0] = 0;
            for (int i = 1; i <= n; i++)
                if (mpos.count(prefix[i]) == 0)
                    mpos[prefix[i]] = i;
            for (int i = 1; i <= n; i++)
                pos[(prefix[i] % prefix[n] + prefix[n]) % prefix[n]].push_back(i);
            for (auto &pii : pos)
            {
                sort(pii.second.begin(), pii.second.end(), [](const int &lhs, const int &rhs)
                     { return calc(lhs) < calc(rhs); });
                vector<int> proc = pii.second;
                vector<int> res;
                res.push_back(proc[0]);
                for (int i = 1, siz = proc.size(); i < siz; i++)
                    if (prefix[proc[i]] < prefix[*res.rbegin()])
                        res.push_back(proc[i]);
                pii.second = res;
            }
            while (m--)
            {
                ll x;
                scanf("%lld", &x), x *= sgn;
                if (mpos.count(x))
                {
                    printf("%d\n", mpos[x]);
                    continue;
                }
                ll px = (x % prefix[n] + prefix[n]) % prefix[n];
                ll ans = 0x7fffffffffffffff;
                prefix[0] = x;
                auto iter = lower_bound(pos[px].begin(), pos[px].end(), 0, [](const int &lhs, const int &rhs)
                                        { return prefix[lhs] > prefix[rhs]; });
                prefix[0] = 0;
                if (iter != pos[px].end() && x - prefix[*iter] >= 0 && (x - prefix[*iter]) % prefix[n] == 0)
                {
                    int subpos = *iter;
                    ans = min(ans, subpos + 1LL * n * ll((x - prefix[subpos]) / prefix[n]));
                }
                if (ans == 0x7fffffffffffffff)
                    puts("-1");
                else
                    printf("%lld\n", ans);
            }
        }
    }
    return 0;
}