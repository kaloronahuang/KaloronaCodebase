// quick_pow.cpp
#include <iostream>
#include <cstring>
using namespace std;
#define ll long long
int k;

ll quick_pow(ll base, long long time)
{
    if (time == 0)
        return 1 % k;
    if (time == 1)
        return base % k;
    if (time % 2 == 0)
    {
        ll res = quick_pow(base, (int)time / 2) % k;
        return (res * res) % k;
    }
    else
        return (quick_pow(base, (int)(time / 2)) * quick_pow(base, (int)(time / 2) + 1)) % k;
}

int main()
{
    int b, p;
    cin >> b >> p >> k;
    ll res = quick_pow(b, p);
    cout << b << "^" << p << " mod " << k << "=" << res;
    return 0;
}
