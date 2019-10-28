// math.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

ll n;
vector<ll> vec;

int main()
{
    scanf("%lld", &n);
    for (ll i = 2; 1LL * i * i <= n; i++)
        if (n % i == 0)
        {
            if (i & 1)
                vec.push_back(n * (i - 1) / i);
            if ((n / i) & 1)
                vec.push_back(n * ((n / i) - 1) / (n / i));
        }
    if ((n & 1) && n != 1)
        vec.push_back(n - 1);
    sort(vec.begin(), vec.end());
    printf("%d ", (int)vec.size());
    for (int i = 0, siz = vec.size(); i < siz; i++)
        printf("%lld ", vec[i]);
    return 0;
}
