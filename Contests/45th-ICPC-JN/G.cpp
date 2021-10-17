// G.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll X, Y;
    scanf("%lld%lld", &X, &Y);
    ll mid = (X ^ Y);
    if (mid < X)
        printf("1\n%lld\n", mid);
    else
    {
        int max_pos = -1;
        for (int i = 63; i > 0; i--)
            if (mid & (1LL << i))
            {
                max_pos = i;
                break;
            }
        printf("2\n%lld %lld\n", mid ^ (1LL << max_pos), (1LL << max_pos));
    }
    return 0;
}