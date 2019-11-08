// CF1243C.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main()
{
    ll n, tmp;
    scanf("%lld", &n), tmp = n;
    for (ll i = 2; 1LL * i * i <= tmp; i++)
        if (tmp % i == 0)
        {
            if (n == tmp)
            {
                int cnt = 0;
                while (tmp % i == 0)
                    cnt++, tmp /= i;
                if (tmp == 1)
                    printf("%lld", i), exit(0);
                else
                    puts("1"), exit(0);
            }
            else
                puts("1"), exit(0);
        }
    printf("%lld", tmp);
    return 0;
}