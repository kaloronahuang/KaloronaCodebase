// P3807.cpp
#include <iostream>

using namespace std;

#define ll long long
ll n, m, p;

inline ll qpow(ll a, ll b)
{
    ll ans = 1;
    a %= p;
    while (b)
    {
        if (b & 1)
            ans = ((ans * a) % p + p) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ans % p;
}
int cnt = 0;
ll process(ll num, ll delta)
{
    while (num % p == 0)
        num /= p, cnt += delta;
    return num;
}

int main()
{
    int sets;
    cin >> sets;
    for (int h = 0; h < sets; h++)
    {
        cin >> n >> m >> p;
        cnt = 0;
        n = n + m;
        ll ans = 1;
        for (int upper = n; upper >= n - m + 1; upper--)
            ans = (ans * process(upper, 1) % p);
        for (int i = m; i > 0; i--)
            ans = (ans * qpow(process(i, -1), p - 2) % p);
        cout << ((cnt == 0) ? ans : 0) << endl;
    }
    return 0;
}