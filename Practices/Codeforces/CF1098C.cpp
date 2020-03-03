// CF1098C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, dep[MAX_N], cnt[MAX_N];
ll S;

bool check(int branch)
{
    memset(dep, 0, sizeof(dep)), memset(cnt, 0, sizeof(cnt));
    ll pos = 1, cdep = 0, alloc = S - n;
    for (int i = 2; i <= n;)
    {
        pos *= branch, cdep++;
        for (int j = 1; j <= pos && i <= n; i++, j++)
            cnt[cdep]++, dep[i] = cdep, alloc -= cdep;
    }
    if (alloc < 0)
        return false;
    int ptr = n;
    while (alloc)
    {
        cdep++;
        if (cnt[dep[ptr]] == 1)
            ptr--;
        pos = min(alloc, cdep - dep[ptr]);
        cnt[dep[ptr]]--, dep[ptr] += pos, cnt[dep[ptr]]++;
        alloc -= pos, ptr--;
    }
    return true;
}

int main()
{
    scanf("%d%lld", &n, &S);
    if (S < (2 * n - 1) || S > (1LL * n * (n + 1) / 2))
        puts("No"), exit(0);
    int l = 1, r = n, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    check(res), memset(cnt, 0, sizeof(cnt));
    puts("Yes"), dep[1] = 0, sort(dep + 2, dep + n + 1);
    for (int i = 2, ptr = 1; i <= n; i++)
    {
        while (dep[ptr] != dep[i] - 1 || cnt[ptr] == res)
            ptr++;
        printf("%d ", ptr), cnt[ptr]++;
    }
    return 0;
}