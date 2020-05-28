// CF1358F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

ll n, ai[MAX_N], bi[MAX_N];
string ans;

bool compare(ll *src, ll *dst)
{
    for (int i = 1; i <= n; i++)
        if (src[i] != dst[i])
            return false;
    return true;
}

bool compareRev(ll *src, ll *dst)
{
    for (int i = 1; i <= n; i++)
        if (src[i] != dst[n - i + 1])
            return false;
    return true;
}

void reduce()
{
    for (int i = n; i >= 1; i--)
        bi[i] -= bi[i - 1];
}

void output(ll remR, ll remP)
{
    reverse(ans.begin(), ans.end());
    if (remP > 2e5)
        printf("BIG\n%lld\n", remP);
    else
    {
        printf("SMALL\n%lld\n", 1LL * ans.size());
        cout << ans << endl;
    }
}

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &bi[i]);
    if (n == 1)
    {
        if (ai[1] == bi[1])
            printf("SMALL\n0\n");
        else
            puts("IMPOSSIBLE");
        return 0;
    }
    ll cnt_rollback = 0, cnt_rev = 0;
    bool huge = false, valid = false;
    if (n > 2)
    {
        while (!(compare(ai, bi) || compareRev(ai, bi)))
        {
            for (int i = 1; i < n; i++)
                if (bi[i] >= bi[i + 1])
                {
                    reverse(bi + 1, bi + 1 + n), ans += 'R', cnt_rev++;
                    break;
                }
            reduce(), cnt_rollback++;
            if (cnt_rollback > 2e5)
                huge = true;
            if (!huge)
                ans += 'P';
            for (int i = 1; i <= n; i++)
                if (bi[i] < 0)
                    puts("IMPOSSIBLE"), exit(0);
        }
        if (compareRev(ai, bi))
            valid = true;
    }
    else
    {
        while (true)
        {
            if (ai[2] == bi[1])
                swap(ai[1], ai[2]), valid = true;
            if (ai[1] == bi[1])
            {
                if (bi[2] < ai[2])
                    puts("IMPOSSIBLE"), exit(0);
                ll steps = (bi[2] - ai[2]) % bi[1];
                if (steps == 0)
                {
                    ll margin = (bi[2] - ai[2]) / bi[1];
                    cnt_rollback += margin;
                    if (cnt_rollback > 2e5)
                        huge = true;
                    if (!huge)
                        for (int i = 1; i <= margin; i++)
                            ans += 'P';
                }
                else
                    puts("IMPOSSIBLE"), exit(0);
                break;
            }
            if (bi[1] < ai[1])
                puts("IMPOSSIBLE"), exit(0);
            ll &x = bi[1], &y = bi[2];
            ll steps = (y - y % x) / x;
            y %= x;
            cnt_rollback += steps;
            if (cnt_rollback > 2e5)
                huge = true;
            if (!huge)
                for (int i = 1; i <= steps; i++)
                    ans += 'P';
            swap(x, y), cnt_rev++, ans += 'R';
        }
    }
    if (valid)
        cnt_rev++, ans += 'R';
    output(cnt_rev, cnt_rollback);
    return 0;
}