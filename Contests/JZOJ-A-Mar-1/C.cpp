// C.
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
const int MAX_N = 1e5 + 2000, mod = 998244353, magicNum = 133;
int n, k;
char str[MAX_N];
ull hashMem[MAX_N], pows[MAX_N];
ll ans;
map<ull, ll> mp;
vector<ull> vec;
ull getHash(int l, int r)
{
    return hashMem[r] - hashMem[l - 1] * pows[r - l + 1];
}
int main()
{
    scanf("%d%d", &n, &k), scanf("%s", str + 1);
    pows[0] = 1;
    for (int i = 1; i <= n; i++)
        hashMem[i] = hashMem[i - 1] * magicNum + str[i] - 'a' + 1, pows[i] = pows[i - 1] * magicNum;
    for (int i = 1; i <= n; i++)
        for (int j = i; j - i + 1 <= k; j++)
            mp[getHash(i, j)]++, vec.push_back(getHash(i, j));
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for (vector<ull>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        ll tmp = mp[*it];
        ans = (ans + ((tmp % mod * (tmp - 1) % mod) >> 1)) % mod;
    }
    printf("%lld", ans);
    return 0;
}