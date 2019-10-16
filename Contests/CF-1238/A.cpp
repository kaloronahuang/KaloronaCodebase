// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int n;
ll x, y;

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        scanf("%lld%lld", &x, &y);
        ll diff = x - y;
        puts(diff == 1 ? "NO" : "YES");
    }
    return 0;
}