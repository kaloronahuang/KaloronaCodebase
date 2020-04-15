// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 7, MAX_LEN = 110, MAX_M = 550, MAX_NODE = MAX_LEN * MAX_N << 1, mod = 998244353;

int n, m, ptot, ch[MAX_NODE][2], tag_pos[MAX_NODE], tag_end[MAX_NODE], fail[MAX_NODE], dp[MAX_M][MAX_NODE][1 << MAX_N];
char org[MAX_N][MAX_LEN];

void insert(char *str, int idx)
{
    int p = 0;
    for (int i = 1; str[i]; i++)
    {
        if (ch[p][str[i] - '0'] == 0)
            ch[p][str[i] - '0'] = ++ptot;
        p = ch[p][str[i] - '0'];
    }
    tag_pos[p] |= (1 << idx);
}

void build_fail()
{
    queue<int> q;
    for (int i = 0; i <= 1; i++)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i <= 1; i++)
            if (ch[u][i])
            {
                fail[ch[u][i]] = ch[fail[u]][i];
                tag_pos[ch[u][i]] |= tag_pos[fail[ch[u][i]]], tag_end[ch[u][i]] |= tag_end[fail[ch[u][i]]];
                q.push(ch[u][i]);
            }
            else
                ch[u][i] = ch[fail[u]][i];
    }
}

int main()
{
    scanf("%d%d", &n, &m), ch[0][0] = ++ptot, ch[0][1] = ++ptot;
    for (int i = 1; i <= n; i++)
        scanf("%s", org[i] + 1), insert(org[i], i - 1);
    for (int i = 1; i <= n; i++)
    {
        // insert the splitting shit;
        int len = strlen(org[i] + 1), p = 0;
        for (int sptr = 1; sptr < ((len + 1) >> 1); sptr++)
            p = ch[p][org[i][sptr] - '0'];
        for (int sptr = (len + 1) >> 1; sptr < len; sptr++)
        {
            // [1, sptr] || [sptr + 1, len];
            p = ch[p][org[i][sptr] - '0'];
            int lptr = sptr, rptr = sptr + 1;
            bool flag = true;
            while (lptr >= 1 && rptr <= len)
                flag &= (org[i][lptr] != org[i][rptr]), lptr--, rptr++;
            if (flag)
                tag_end[p] |= (1 << (i - 1));
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int len = strlen(org[i] + 1);
        reverse(org[i] + 1, org[i] + 1 + len);
        for (int j = 1; j <= len; j++)
            org[i][j] ^= 1;
        insert(org[i], i - 1);
        int p = 0;
        for (int sptr = 1; sptr < (len >> 1) + 1; sptr++)
            p = ch[p][org[i][sptr] - '0'];
        for (int sptr = (len >> 1) + 1; sptr < len; sptr++)
        {
            // [1, sptr] || [sptr + 1, len];
            p = ch[p][org[i][sptr] - '0'];
            int lptr = sptr, rptr = sptr + 1;
            bool flag = true;
            while (lptr >= 1 && rptr <= len)
                flag &= (org[i][lptr] != org[i][rptr]), lptr--, rptr++;
            if (flag)
                tag_end[p] |= (1 << (i - 1));
        }
    }
    build_fail();
    dp[0][0][0] = 1;
    for (int i = 0; i < m; i++)
        for (int p = 0; p <= ptot; p++)
            for (int c = 0; c < 2; c++)
                if (ch[p][c])
                    for (int mask = 0; mask < (1 << n); mask++)
                        dp[i + 1][ch[p][c]][mask | tag_pos[ch[p][c]]] = (0LL + dp[i + 1][ch[p][c]][mask | tag_pos[ch[p][c]]] + dp[i][p][mask]) % mod;
    int ans = 0;
    for (int p = 0; p <= ptot; p++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (dp[m][p][mask])
                if ((mask | tag_end[p]) == (1 << n) - 1)
                    ans = (0LL + ans + dp[m][p][mask]) % mod;
    printf("%d\n", ans);
    return 0;
}