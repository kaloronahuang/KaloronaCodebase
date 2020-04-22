// BZ1319.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll p, k, abase;

ll fpow(ll bas, ll tim, ll cmod)
{
    ll ret = 1;
    for (; tim; tim >>= 1, bas = bas * bas % cmod)
        if (tim & 1)
            ret = 1LL * ret * bas % cmod;
    return ret;
}

ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), tmp = x;
    x = y, y = tmp - (a / b) * y;
    return d;
}

ll solveRoot()
{
    ll acc = p - 1;
    vector<ll> st;
    for (int i = 2; 1LL * i * i <= acc; i++)
        if (acc % i == 0)
        {
            st.push_back(i);
            while (acc % i == 0)
                acc /= i;
        }
    if (acc != 1)
        st.push_back(acc);
    for (ll g_ = 2;; g_++)
    {
        bool flag = true;
        for (int i = 0, siz = st.size(); i < siz; i++)
            if (fpow(g_, (p - 1) / st[i], p) == 1)
            {
                flag = false;
                break;
            }
        if (flag)
            return g_;
    }
    return -1;
}

map<ll, ll> ump;

ll bsgs(ll base, ll x, ll cmod)
{
    // get i : base^i = x \bmod cmod;
    ll block = ceil(sqrt(cmod));
    ump.clear();
    for (ll j = 0, acc = 1; j <= block; j++, acc = 1LL * acc * base % cmod)
        ump[acc * x % cmod] = j;
    ll unit = fpow(base, block, cmod);
    for (ll j = 1, acc = unit; j <= block; j++, acc = 1LL * acc * unit % cmod)
        if (ump.count(acc))
            return j * block - ump[acc];
    return -1;
}

int main()
{
    scanf("%lld%lld%lld", &p, &k, &abase);
    if (abase == 0)
        puts("0"), exit(0);
    if (p == 2)
    {
        if (abase == 1)
            printf("1\n1\n");
        else
            printf("1\n0\n");
        return 0;
    }
    if (p == 3)
    {
        vector<ll> vec;
        for (int i = 0; i < 3; i++)
            if (fpow(i, k, p) == abase)
                vec.push_back(i);
        printf("%lld\n", 1LL * vec.size());
        for (int i = 0, siz = vec.size(); i < siz; i++)
            printf("%lld ", vec[i]);
    }
    ll g = solveRoot(), m = bsgs(g, abase, p), x, y, d = exgcd(k, p - 1, x, y), unit = (p - 1) / d;
    if (m % d != 0)
        puts("0"), exit(0);
    x = 1LL * x * (m / d) % (p - 1), x = (0LL + x + p - 1) % (p - 1);
    vector<ll> ansBox;
    for (ll i = 0; i < d; i++)
        ansBox.push_back(fpow(g, x, p)), x += unit;
    sort(ansBox.begin(), ansBox.end());
    printf("%lld\n", 1LL * ansBox.size());
    for (int i = 0, siz = ansBox.size(); i < siz; i++)
        printf("%lld ", ansBox[i]);
    return 0;
}