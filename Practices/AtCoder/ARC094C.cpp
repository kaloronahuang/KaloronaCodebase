// ARC094C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;

int n, ai[MAX_N], bi[MAX_N];
priority_queue<pii> pq1;
multiset<pii> pq2;

int main()
{
    scanf("%d", &n);
    long long ans = 0, acc = 1LL << 30;
    bool flag = true;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &ai[i], &bi[i]);
        flag &= (ai[i] == bi[i]), ans += ai[i];
        if (ai[i] > bi[i])
            acc = min(acc, 1LL * bi[i]);
    }
    if (flag)
        puts("0");
    else
        printf("%lld\n", ans - acc);
    return 0;
}