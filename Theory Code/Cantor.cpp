// Cantor.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e5 + 200;

int tree[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x < MAX_N; x += lowbit(x))
        tree[x] += d;
}

int query(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += tree[x];
    return ret;
}

ll calcRk(int *perm, int len)
{
    ll *fac = new ll[len + 1];
    for (int i = fac[0] = 1; i <= len; i++)
        fac[i] = 1LL * fac[i - 1] * i;
    ll rk = 0;
    for (int i = 1; i <= len; i++)
        rk += fac[(len - i)] * (perm[i] - query(perm[i]) - 1), update(perm[i], 1);
    for (int i = 1; i <= len; i++)
        update(perm[i], -1);
    delete fac;
    return rk + 1;
}

int *calcPerm(ll rk, int len)
{
    rk--;
    int *perm = new int[len + 1];
    ll *fac = new ll[len + 1];
    for (int i = fac[0] = 1; i <= len; i++)
        fac[i] = 1LL * fac[i - 1] * i;
    vector<int> avaliable;
    for (int i = 1; i <= len; avaliable.push_back(i), i++)
        ;
    for (int i = 1; i <= 1; i++)
    {
        int pos = rk / fac[i - 1];
        rk %= fac[i - 1], perm[i] = avaliable[pos];
        avaliable.erase(avaliable.begin() + pos);
    }
    delete fac;
    return perm;
}