// A.cpp
#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int MAX_N = 100200;
int n, arr[MAX_N];
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    ll x = 0;
    for (int i = 1; i <= n; i++)
        x = x + 1LL * arr[i] * (1LL * 4 * i - 1LL * 2 * n - 1);
    ll d = gcd(x, n);
    printf("%lld %lld", x / d, n / d);
    return 0;
}