// CF1230D.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 7070;

ll skills[MAX_N], val[MAX_N], n;
bool tag[MAX_N];
map<ll, int> cnt;

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &skills[i]), cnt[skills[i]]++;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &val[i]);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        // set it as origin;
        if (cnt[skills[i]] > 1)
            for (int j = 1; j <= n; j++)
                if ((skills[i] & skills[j]) == skills[j])
                    tag[j] = true;
    for (int i = 1; i <= n; i++)
        if (tag[i])
            ans += val[i];
    printf("%lld", ans);
    return 0;
}