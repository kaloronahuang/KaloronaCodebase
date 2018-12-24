// P2602.cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll l, r, cnta[10], cntb[10], f[16], ten[16];
void solve(ll num, ll cnt[])
{
    ll narr[20];
    int len = 0;
    while (num)
        narr[++len] = num % 10, num /= 10;
    for (int i = len; i; i--)
    {
        ll curt = narr[i];
        for (int j = 0; j < 10; j++)
            cnt[j] += f[i - 1] * curt;
        for (int j = 0; j < curt; j++)
            cnt[j] += ten[i - 1];
        ll numal = 0;
        for (int j = i - 1; j >= 1; j--)
            numal = numal * 10 + narr[j];
        cnt[narr[i]] += numal + 1;
        cnt[0] -= ten[i - 1];
    }
}
int main()
{
    scanf("%lld%lld", &l, &r);
    ten[0] = 1;
    for (int i = 1; i <= 15; i++)
        f[i] = f[i - 1] * 10 + ten[i - 1], ten[i] = 10 * ten[i - 1];
    solve(l - 1, cnta), solve(r, cntb);
    for (int i = 0; i < 10; i++)
        printf("%lld ", cntb[i] - cnta[i]);
    return 0;
}