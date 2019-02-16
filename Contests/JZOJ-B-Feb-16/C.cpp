// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 100010;
int n, k, p, ans = 0x7f7f7f7f, s[MAX_N];
set<int> st;
int main()
{
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 1; i <= n; i++)
        scanf("%d", &s[i]), (s[i] += s[i - 1]) %= p;
    set<int>::iterator it;
    st.insert(s[n]);
    for (int i = n - 1; i >= 1; i--)
    {
        it = st.lower_bound(s[i] + k);
        if (it != st.end())
            ans = min(*it - s[i], ans);
        it = st.lower_bound(s[i] + k - p);
        if (it != st.end() && *it < s[i])
            ans = min(*it - s[i] + p, ans);
        st.insert(s[i]);
    }
    printf("%d", ans);
    return 0;
}