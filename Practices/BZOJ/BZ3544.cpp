// BZ3544.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n;
long long ans, mod, ai[MAX_N];

int main()
{
    scanf("%d%lld", &n, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]), ai[i] = (0LL + ai[i] % mod + mod) % mod;
    set<long long> st;
    st.insert(0);
    long long pre = 0;
    for (int i = 1; i <= n; i++)
    {
        pre = (0LL + pre + ai[i]) % mod;
        set<long long>::iterator it = st.upper_bound(pre);
        if (it != st.end())
            ans = max(ans, (pre + mod - *it) % mod);
        else
            ans = max(ans, pre);
        st.insert(pre);
    }
    printf("%lld\n", ans);
    return 0;
}