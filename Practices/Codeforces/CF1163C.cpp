// CF1163C.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>
#define st set<int>

using namespace std;

const int MAX_N = 1010;

int xi[MAX_N], yi[MAX_N], n;

map<pr, st> mp;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
        {
            int A = yi[j] - yi[i], B = xi[i] - xi[j], C = xi[j] * yi[i] - xi[i] * yi[j];
            int d = __gcd(A, B);
            A /= d, B /= d, C /= d;
            pr now = make_pair(A, B);
            mp[now].insert(C);
        }
    ll ans = 0, prefix = 0;
    map<pr, st>::iterator it;
    for (it = mp.begin(); it != mp.end(); it++)
    {
        ans += (it->second).size() * prefix;
        prefix += (it->second).size();
    }
    printf("%lld", ans);
    return 0;
}