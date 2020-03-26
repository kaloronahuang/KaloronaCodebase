// UOJ82.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22;

typedef long long ll;
typedef pair<int, int> pii;

int n;
ll m;
vector<pii> mfac;

int main()
{
    scanf("%d%lld", &n, &m);
    ll acc = 1;
    for (int i = 1; i <= n; i++)
        acc *= i;
    for (int i = 1; i <= n; i++)
    {
        if (m >= acc)
            printf("%lld\n", (ll)(m / acc) * acc);
        m %= acc, acc /= i;
    }
    if (m)
        printf("%lld\n", m);
    return 0;
}