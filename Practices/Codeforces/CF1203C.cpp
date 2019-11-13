// CF1203C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 4e5 + 400;

int n;
ll seq[MAX_N];

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &seq[i]);
    ll di = seq[1], ans = 0;
    for (int i = 2; i <= n; i++)
        di = gcd(di, seq[i]);
    for (int i = 1; 1LL * i * i <= di; i++)
        if (di % i == 0)
        {
            ans++;
            if (i != (di / i))
                ans++;
        }
    printf("%lld", ans);
    return 0;
}