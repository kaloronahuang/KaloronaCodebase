// POJ3889.cpp
#include <iostream>
#include <cmath>
#include <iomanip>
#define ll long long
using namespace std;
ll total;

pair<ll, ll> calc(ll N, ll M)
{
    if (N == 0)
        return make_pair((ll)0, (ll)0);
    ll scale = 1 << (2 * N), len = 1 << (N - 1);
    ll rg = 1 << (2 * N - 2);
    pair<ll, ll> res = calc(N - 1, M % rg);
    ll pt = M / rg;
    if (pt == 0)
        return make_pair(res.second, res.first);
    if (pt == 1)
        return make_pair(res.first, res.second + len);
    if (pt == 2)
        return make_pair(res.first + len, res.second + len);
    if (pt == 3)
        return make_pair(2 * len - res.second - 1, len - res.first - 1);
}

int main()
{
    cin >> total;
    for (int i = 0; i < total; i++)
    {
        ll range, idx1, idx2;
        cin >> range >> idx1 >> idx2;
        pair<ll, ll> pa = calc(range, idx1 - 1), pb = calc(range, idx2 - 1);
        double res = sqrt((pa.first - pb.first) * (pa.first - pb.first) + (pa.second - pb.second) * (pa.second - pb.second));
        cout << fixed << setprecision(0) << res * 10 << endl;
    }
    return 0;
}