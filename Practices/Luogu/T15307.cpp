// T15307.cpp
#include <iostream>

using namespace std;

#define ll long long
ll a, b;
const ll p = 1000000007;

ll quick_pow(ll base, ll tim, ll mod)
{
    ll temp = 1;
    while (tim)
    {
        if (tim % 2 == 1)
            temp = (temp % mod) * (base % mod) % mod;
        base = (base % mod) * (base % mod) % mod;
        tim >>= 1;
    }
    return temp;
}

int main()
{
    cin >> a >> b;
    ll res = quick_pow(a, b - 1, p - 1);
    cout << quick_pow(a, res, p);
    return 0;
}