// A.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll n, A, B, ans = 0x7fffffffffffffff;
    scanf("%lld%lld%lld", &n, &A, &B);
    ans = min(A - 1, n - B) + 1 + ((B - A - 1) >> 1);
    if (!((A^B) & 1))
        ans = min(ans, (B - A) >> 1);
    printf("%lld\n", ans);
    return 0;
}