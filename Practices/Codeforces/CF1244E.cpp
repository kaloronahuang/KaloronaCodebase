// CF1244E.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, ll>

using namespace std;

const int MAX_N = 1e5 + 200;

ll n, seq[MAX_N], k, prefix[MAX_N];
set<pr> st;

bool check(ll mid)
{
    for (int i = 1; i <= n; i++)
    {
        set<pr>::iterator it = st.lower_bound(make_pair(seq[i] - mid, 0));
        ll lft = 0, rig = 0;
        if (it != st.begin())
        {
            it--;
            lft = (seq[i] - mid) * ((*it).second) - prefix[((*it).second)];
        }
        rig = (prefix[n] - prefix[i]) - (n - i) * seq[i];
        if (lft + rig <= k)
            return true;
        it = st.lower_bound(make_pair(seq[i] + mid, 0));
        lft = rig = 0;
        if (it != st.end())
            rig = (prefix[n] - prefix[((*it).second) - 1]) - (n - ((*it).second) + 1) * (seq[i] + mid);
        lft = i * seq[i] - prefix[i];
        if (lft + rig <= k)
            return true;
    }
    return false;
}

int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &seq[i]);
    sort(seq + 1, seq + 1 + n);
    for (int i = 1; i <= n; i++)
        st.insert(make_pair(seq[i], i));
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + seq[i];
    ll l = 0, r = 1e18, ans = 0;
    while (l <= r)
    {
        ll mid = (l + r) / 2;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%lld", ans);
    return 0;
}