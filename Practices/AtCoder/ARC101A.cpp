// ARC101A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, k, ai[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    ll gans = 1e18;
    for (int lft = 1; lft <= n - k + 1; lft++)
        if (ai[lft] <= 0 && ai[lft + k - 1] >= 0)
            gans = min(gans, 0LL + ai[lft + k - 1] - ai[lft] + min(abs(ai[lft + k - 1]), abs(ai[lft])));
    int zero_pt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (ai[i] >= 0 && zero_pt == 0)
            zero_pt = i;
        if (ai[i] >= 0 && i - zero_pt + 1 == k)
            gans = min(gans, 0LL + ai[i]);
    }
    if (zero_pt == 0)
        zero_pt = n + 1;
    for (int i = 1; i <= n; i++)
        if (ai[i] <= 0 && zero_pt - i == k)
            gans = min(gans, 0LL - ai[i]);
    printf("%lld\n", gans);
    return 0;
}