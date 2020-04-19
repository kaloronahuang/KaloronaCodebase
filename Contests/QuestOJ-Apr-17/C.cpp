// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e4 + 200, base = 133;

typedef unsigned long long ull;

int T, n, m, dp[1 << 4][MAX_N], len[4], q[MAX_N], prod[MAX_N], head, tail, id[4];
ull prehash[MAX_N], mhash[4], pownum[MAX_N];
char str[4][MAX_N], org[MAX_N];
string pool[4];

ull getHash(int l, int r) { return prehash[r] - prehash[l - 1] * pownum[r - l + 1]; }

int main()
{
    for (int i = pownum[0] = 1; i < MAX_N; i++)
        pownum[i] = 1LL * pownum[i - 1] * base;
    scanf("%d", &T);
    while (T--)
    {
        memset(len, 0, sizeof(len)), memset(q, 0, sizeof(q)), memset(prod, 0, sizeof(prod));
        head = tail = 0, memset(prehash, 0, sizeof(prehash)), memset(mhash, 0, sizeof(mhash));
        scanf("%s%d", org + 1, &m), n = strlen(org + 1);
        for (int i = pownum[0] = 1; i <= n; i++)
            prehash[i] = prehash[i - 1] * base + org[i] - 'a';
        for (int i = 0; i < m; i++)
            cin >> pool[i];
        sort(pool, pool + m, [](const string &s1, const string &s2) { return s1.length() > s2.length(); });
        int tot = 0;
        for (int i = 0; i < m; i++)
        {
            bool flag = true;
            for (int j = 0; j < i; j++)
            {
                if (pool[j].find(pool[i]) != -1)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                tot++;
                for (int j = 0; j < pool[i].length(); j++)
                    str[i][j + 1] = pool[i][j];
                str[i][pool[i].length() + 1] = 0;
            }
        }
        int pre = m;
        m = tot;
        memset(mhash, 0, sizeof(mhash));
        for (int i = 0; i < m; i++)
        {
            len[i] = strlen(str[i] + 1);
            for (int j = 1; j <= len[i]; j++)
                mhash[i] = mhash[i] * base + str[i][j] - 'a';
        }
        // min_val first;
        memset(dp, 0x3f, sizeof(dp));
        memset(dp[0], 0, sizeof(dp[0]));
        for (int stat = 1; stat < (1 << m); stat++)
            for (int j = 0; j < m; j++)
                if (stat & (1 << j))
                {
                    head = 1, tail = 0;
                    for (int i = 1, min_val = 0x3f3f3f3f; i <= n; i++)
                    {
                        if (i - len[j] >= 0)
                            min_val = min(min_val, dp[stat ^ (1 << j)][i - len[j]]);
                        if ((stat ^ (1 << j)) != 0)
                        {
                            while (head <= tail && q[head] <= i - len[j])
                                head++;
                            while (head <= tail && dp[stat ^ (1 << j)][i] - i <= prod[tail])
                                tail--;
                            q[++tail] = i, prod[tail] = dp[stat ^ (1 << j)][i] - i;
                        }
                        if (i - len[j] + 1 >= 1 && getHash(i - len[j] + 1, i) == mhash[j])
                        {
                            dp[stat][i] = min(dp[stat][i], min_val + len[j]);
                            if (head <= tail)
                                dp[stat][i] = min(dp[stat][i], i + prod[head]);
                        }
                    }
                }
        int min_val = 0x3f3f3f3f;
        for (int i = 1; i <= n; i++)
            min_val = min(min_val, dp[(1 << m) - 1][i]);
        printf("%d ", min_val), m = pre;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < pool[i].length(); j++)
                str[i][j + 1] = pool[i][j];
            str[i][pool[i].length() + 1] = 0;
            len[i] = strlen(str[i] + 1);
        }
        // max_val second;
        for (int i = 0; i < m; i++)
            id[i] = i;
        int max_val = 0;
        do
        {
            memset(dp, 0, sizeof(dp));
            for (int stat = 1; stat < (1 << m); stat++)
                for (int j = 0; j < m; j++)
                    if (stat & (1 << j))
                    {
                        head = 1, tail = 0;
                        for (int i = 1, max_val = 0; i <= n; i++)
                        {
                            if (i - len[id[j]] >= 0)
                                max_val = max(max_val, dp[stat ^ (1 << j)][i - len[id[j]]]);
                            if ((stat ^ (1 << j)) != 0)
                            {
                                while (head <= tail && q[head] <= i - len[id[j]])
                                    head++;
                                while (head <= tail && dp[stat ^ (1 << j)][i] - i >= prod[tail])
                                    tail--;
                                q[++tail] = i, prod[tail] = dp[stat ^ (1 << j)][i] - i;
                            }
                            if (i - len[id[j]] + 1 >= 1 && getHash(i - len[id[j]] + 1, i) == mhash[id[j]])
                            {
                                dp[stat][i] = max(dp[stat][i], max_val + len[id[j]]);
                                if (head <= tail)
                                    dp[stat][i] = max(dp[stat][i], i + prod[head]);
                            }
                        }
                    }
            for (int i = 1; i <= n; i++)
                max_val = max(max_val, dp[(1 << m) - 1][i]);
        } while (next_permutation(id, id + m));
        printf("%d\n", max_val);
    }
    return 0;
}