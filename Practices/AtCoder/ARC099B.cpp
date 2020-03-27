// ARC099B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

double count(ll i)
{
    ll sum = 0, x = i;
    while (x)
        sum += x % 10, x /= 10;
    return 1.0 * i / sum;
}

int main()
{
    ll k;
    scanf("%lld", &k);
    ll cnt = 0, curt = 0, base = 1;
    while (cnt < k)
        if ((curt / base) % 10 != 9)
        {
            curt += base, cnt++;
            printf("%lld\n", curt);
        }
        else
        {
            if (count(curt + base) > count(curt + base * 10))
                base *= 10;
            curt += base, cnt++;
            printf("%lld\n", curt);
        }
    return 0;
}