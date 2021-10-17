// E.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int T;
ll p;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &p);
        printf("%lld 3\n", 6LL * p);
        printf("%lld %lld %lld\n", 1LL * p, 2LL * p, 3LL * p);
    }
    return 0;
}