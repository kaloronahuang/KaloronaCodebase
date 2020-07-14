// CF1380D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;

int n, m, x, k, y, ai[MAX_N], bi[MAX_N];
vector<pii> ints;

int main()
{
    scanf("%d%d%d%d%d", &n, &m, &x, &k, &y);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]);
    int last_ptr = 1, last_sync = 0;
    for (int i = 1; i <= n; i++)
    {
        if (bi[last_ptr] == ai[i])
        {
            if (i - 1 > last_sync)
                ints.push_back(make_pair(last_sync + 1, i - 1));
            last_ptr++, last_sync = i;
        }
    }
    if (n > last_sync)
        ints.push_back(make_pair(last_sync + 1, n));
    if (last_ptr != m + 1)
        puts("-1"), exit(0);
    long long ret = 0;
    for (pii curt : ints)
    {
        int ub = max(ai[curt.first - 1], ai[curt.second + 1]), mcnt = 0, len = curt.second - curt.first + 1;
        for (int i = curt.first; i <= curt.second; i++)
            if (ai[i] > ub)
                mcnt++;
        if (1LL * y * k < x && mcnt == 0)
            ret += 1LL * y * len;
        else
        {
            if (1LL * y * k < x)
            {
                // mcnt > 0;
                int units = (mcnt + k - 1) / k;
                if (len < 1LL * k * units)
                    puts("-1"), exit(0);
                ret += 1LL * units * x + 1LL * y * (len - 1LL * k * units);
            }
            else
            {
                if (mcnt > len - len % k)
                    puts("-1"), exit(0);
                long long pans = 1LL << 62;
                for (int i = 0; 1LL * i * k <= len; i++)
                    if (mcnt <= 1LL * i * k)
                        pans = min(pans, 1LL * i * x + 1LL * (len - 1LL * i * k) * y);
                ret += pans;
            }
        }
    }
    printf("%lld\n", ret);
    return 0;
}