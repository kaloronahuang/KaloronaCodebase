// C.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll T, x_1, x_2, x_3, y_1, y_2, y_3;

long double getDist(ll x, ll y, ll a, ll b) { return sqrt((x - a) * (x - a) + (y - b) * (y - b)); }

int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        scanf("%lld%lld%lld%lld%lld%lld", &x_1, &y_1, &x_2, &y_2, &x_3, &y_3);
        printf("%lld\n", (ll)getDist(x_1, y_1, x_2, y_2) + getDist(x_2, y_2, x_3, y_3) + getDist(x_3, y_3, x_1, y_1));
    }
    return 0;
}