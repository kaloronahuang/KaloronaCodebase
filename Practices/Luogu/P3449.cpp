// P3449.cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const int MAX_N = 2e6 + 200, base = 133;

int T, n;
char str[MAX_N];
ull hval[MAX_N], pownum[MAX_N];
multiset<ull> ms;

ull substr_hash(int l, int r) { return hval[r] - hval[l - 1] * pownum[r - l + 1]; }

bool check(int len, ull val)
{
    for (int i = 1; i <= n; i += len)
        if (substr_hash(i, i + len - 1) != val)
            return false;
    return true;
}

int main()
{
    for (int i = pownum[0] = 1; i < MAX_N; i++)
        pownum[i] = 1LL * pownum[i - 1] * base;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s", &n, str + 1);
        for (int i = 1; i <= n; i++)
            hval[i] = hval[i - 1] * base + str[i] - 'a';
        for (int i = 1; i <= n; i++)
            if (n % i == 0 && check(i, substr_hash(1, i)))
            {
                ms.insert(substr_hash(1, i));
                break;
            }
    }
    long long ans = 0;
    while (!ms.empty())
    {
        ull ft = *ms.begin();
        ans += 1LL * ms.count(ft) * ms.count(ft);
        ms.erase(ft);
    }
    printf("%lld\n", ans);
    return 0;
}