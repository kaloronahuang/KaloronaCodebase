// C.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 200;
ll x1, x2, y1, y2, n, xi[MAX_N], yi[MAX_N];
char str[MAX_N];
bool check(ll mid)
{
    ll xdist = x1 + mid / n * xi[n] + xi[mid % n];
    ll ydist = y1 + mid / n * yi[n] + yi[mid % n];
    return abs(x2 - xdist) + abs(y2 - ydist) <= mid;
}
int main()
{
    scanf("%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &n);
    scanf("%s", str + 1);
    for (int i = 1; i <= n; i++)
    {
        switch (str[i])
        {
        case 'U':
            yi[i]++;
            break;
        case 'D':
            yi[i]--;
            break;
        case 'L':
            xi[i]--;
            break;
        case 'R':
            xi[i]++;
            break;
        }
        xi[i] += xi[i - 1], yi[i] += yi[i - 1];
    }
    ll l = 0, r = 1e14, ans = -1;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}