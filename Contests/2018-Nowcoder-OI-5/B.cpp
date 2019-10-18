// B.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int T;
ll n;

ll divide(ll bas)
{
    if (bas <= 2)
        return 0;
    if (bas & 1)
        return divide(bas / 2) + divide(bas / 2 + 1) + 1;
    return divide(bas / 2) << 1;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        /*
        int cnt = 0;
        while (n >= 2)
        {
            if (n & 1)
                n--, cnt++;
            n /= 2;
        }
        */
        printf("%lld\n", divide(n));
    }
    return 0;
}