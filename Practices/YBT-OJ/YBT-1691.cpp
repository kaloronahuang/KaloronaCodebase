// YBT-1691.cpp
#include <bits/stdc++.h>
#define ll long long

const int MAX_N = 2e5 + 200, bitnum = 133, mod1 = 1e9 + 9, mod2 = 1e9 + 7;

using namespace std;

int n, k;
char str[MAX_N];
ll pownum1[MAX_N], pownum2[MAX_N], prefix1[MAX_N], prefix2[MAX_N];
struct node
{
    ll hash1, hash2;
    bool operator<(const node &rhs) const { return hash1 < rhs.hash1 || (hash1 == rhs.hash1 && hash2 < rhs.hash2); }
};
set<node> st;

ll substr(ll *prefix, ll *pownum, int l, int r, int mod) { return (1LL * prefix[r] + mod - 1LL * prefix[l - 1] * pownum[r - l + 1] % mod) % mod; }

int main()
{
    scanf("%d%d%s", &n, &k, str + 1);
    for (int i = pownum1[0] = pownum2[0] = 1; i <= n; i++)
    {
        pownum1[i] = 1LL * pownum1[i - 1] * bitnum % mod1;
        pownum2[i] = 1LL * pownum2[i - 1] * bitnum % mod2;
        prefix1[i] = (1LL * prefix1[i - 1] * bitnum % mod1 + str[i] - 'a' + 1) % mod1;
        prefix2[i] = (1LL * prefix2[i - 1] * bitnum % mod2 + str[i] - 'a' + 1) % mod2;
    }
    for (int i = k; i <= n; i++)
        st.insert(node{substr(prefix1, pownum1, i - k + 1, i, mod1), substr(prefix2, pownum2, i - k + 1, i, mod2)});
    cout << st.size() << endl;
    return 0;
}