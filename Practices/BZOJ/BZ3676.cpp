// BZ3676.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;

int n;
char S[MAX_N];

namespace PAM
{

    int ptot, stot, ch[MAX_N][26], cnt[MAX_N], len[MAX_N], fail[MAX_N], last_ptr;
    char str[MAX_N];

    int newnode(int l)
    {
        ptot++, memset(ch[ptot], 0, sizeof(ch[ptot]));
        len[ptot] = l, fail[ptot] = cnt[ptot] = 0;
        return ptot;
    }

    void clear()
    {
        ptot = -1, last_ptr = 0;
        str[stot = 0] = '$';
        newnode(0), newnode(-1);
        fail[0] = 1;
    }

    int jump(int p)
    {
        while (str[stot - len[p] - 1] != str[stot])
            p = fail[p];
        return p;
    }

    void insert(int c)
    {
        str[++stot] = c;
        int pre = jump(last_ptr);
        if (ch[pre][c] == 0)
        {
            int p = newnode(len[pre] + 2);
            fail[p] = ch[jump(fail[pre])][c];
            ch[pre][c] = p;
        }
        last_ptr = ch[pre][c], cnt[last_ptr]++;
    }

    ll solve()
    {
        ll ans = 0;
        for (int i = ptot; i >= 0; i--)
            cnt[fail[i]] += cnt[i];
        for (int i = 1; i <= ptot; i++)
            ans = max(ans, 1LL * len[i] * cnt[i]);
        return ans;
    }

} // namespace PAM

int main()
{
    scanf("%s", S + 1), PAM::clear();
    for (int i = 1; S[i]; i++)
        PAM::insert(S[i] - 'a');
    printf("%lld\n", PAM::solve());
    return 0;
}