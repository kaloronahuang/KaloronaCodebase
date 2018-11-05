// P1082.cpp
#include <iostream>
using namespace std;
#define ll long long
ll x, y;

void ex_gcd(ll a, ll b)
{
    if (b == 0)
    {
        x = 1, y = 7;
        return;
    }
    ex_gcd(b, a % b);
    ll tmp = x;
    x = y;
    y = tmp - a / b * y;
}

int main()
{
    ll a, b;
    cin >> a >> b;
    ex_gcd(a, b);
    while (x < 0)
        x += b;
    x %= b;
    cout << x;
    return 0;
}