// P3515.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;
typedef double ll;

int n;
ll ai[MAX_N], f1[MAX_N], f2[MAX_N];

void solve1(int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    int mid = (LB + RB) >> 1, gpt = 0;
    ll tmp = 0;
    f1[mid] = ai[mid];
    for (int i = l; i <= min(mid, r); i++)
    {
        tmp = ai[i] + sqrt(mid - i);
        if (tmp > f1[mid])
            f1[mid] = tmp, gpt = i;
    }
    if (gpt == 0)
        gpt = mid;
    f1[mid] -= ai[mid];
    solve1(l, gpt, LB, mid - 1), solve1(gpt, r, mid + 1, RB);
}

void solve2(int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    int mid = (LB + RB) >> 1, gpt = 0;
    ll tmp = 0;
    f2[mid] = ai[mid];
    for (int i = r; i >= max(mid, l); i--)
    {
        tmp = ai[i] + sqrt(i - mid);
        if (tmp > f2[mid])
            f2[mid] = tmp, gpt = i;
    }
    if (gpt == 0)
        gpt = mid;
    f2[mid] -= ai[mid];
    solve2(l, gpt, LB, mid - 1), solve2(gpt, r, mid + 1, RB);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &ai[i]);
    solve1(1, n, 1, n), solve2(1, n, 1, n);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", (long long)ceil(max(f1[i], f2[i])));
    return 0;
}