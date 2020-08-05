// P1659.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200, mod = 19930726;

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

namespace PAM
{

    int ptot, stot, last_ptr, ch[MAX_N][26], len[MAX_N], link[MAX_N], cnt[MAX_N];
    char str[MAX_N];

    int newnode(int l)
    {
        ptot++, memset(ch[ptot], 0, sizeof(ch[ptot]));
        len[ptot] = l, link[ptot] = cnt[ptot] = 0;
        return ptot;
    }

    void clear()
    {
        ptot = -1, str[stot = 0] = '$', last_ptr = 0;
        newnode(0), newnode(-1), link[0] = 1;
    }

    int jump(int p)
    {
        while (str[stot - len[p] - 1] != str[stot])
            p = link[p];
        return p;
    }

    void insert(int c)
    {
        str[++stot] = c;
        int pre = jump(last_ptr);
        if (ch[pre][c] == 0)
        {
            int p = newnode(len[pre] + 2);
            link[p] = ch[jump(link[pre])][c], ch[pre][c] = p;
        }
        last_ptr = ch[pre][c], cnt[last_ptr]++;
    }

} // namespace PAM

int n, idx[MAX_N];
long long k;
char S[MAX_N];

int main()
{
    scanf("%d%lld%s", &n, &k, S + 1), PAM::clear();
    for (int i = 1; i <= n; i++)
        PAM::insert(S[i] - 'a');
    for (int i = 1; i <= PAM::ptot; i++)
        idx[i] = i;
    for (int i = PAM::ptot; i >= 0; i--)
        PAM::cnt[PAM::link[i]] += PAM::cnt[i];
    sort(idx + 1, idx + 1 + PAM::ptot, [](const int &rhs1, const int &rhs2) { return PAM::len[rhs1] > PAM::len[rhs2]; });
    int ans = 1, ptr = 1;
    while (k)
    {
        if (ptr > PAM::ptot)
            puts("-1"), exit(0);
        if (PAM::len[idx[ptr]] % 2 == 1)
            if (PAM::cnt[idx[ptr]] < k)
            {
                k -= PAM::cnt[idx[ptr]];
                ans = 1LL * ans * fpow(PAM::len[idx[ptr]], PAM::cnt[idx[ptr]]) % mod;
            }
            else
                ans = 1LL * ans * fpow(PAM::len[idx[ptr]], k) % mod, k = 0;
        ptr++;
    }
    printf("%d\n", ans);
    return 0;
}