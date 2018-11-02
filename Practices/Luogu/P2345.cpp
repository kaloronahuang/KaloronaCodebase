// P2345.cpp
#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 21000;
#define ll long long
ll n;
ll vi[maxn], xi[maxn];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> vi[i] >> xi[i];
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            ans += max(vi[i], vi[j]) * abs(xi[i] - xi[j]);
    cout << ans;
    return 0;
}