// YBT-OJ1692.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod1 = 1e9 + 7, mod2 = 1e9 + 9, bitnum = 133;

int n, m, pow1[MAX_N], pow2[MAX_N], last_ptr[26][MAX_N];
char S[MAX_N], T[MAX_N];
bool vis[26];

struct hash_val
{
    int val1, val2;

    hash_val operator+(const int &ch)
    {
        hash_val ret = *this;
        ret.val1 = (1LL * ret.val1 + mod1 + ch) % mod1;
        ret.val2 = (1LL * ret.val2 + mod2 + ch) % mod2;
        return ret;
    }

    hash_val operator-(const hash_val &rhs)
    {
        hash_val ret = *this;
        ret.val1 = (0LL + ret.val1 + mod1 - rhs.val1) % mod1;
        ret.val2 = (0LL + ret.val2 + mod2 - rhs.val2) % mod2;
        return ret;
    }

    hash_val operator*(const int &rhs)
    {
        hash_val ret = *this;
        ret.val1 = 1LL * ret.val1 * rhs % mod1;
        ret.val2 = 1LL * ret.val2 * rhs % mod2;
        return ret;
    }

    hash_val operator*(const hash_val &rhs)
    {
        hash_val ret = *this;
        ret.val1 = 1LL * ret.val1 * rhs.val1 % mod1;
        ret.val2 = 1LL * ret.val2 * rhs.val2 % mod2;
        return ret;
    }

    bool operator==(const hash_val &target) const { return val1 == target.val1 && val2 == target.val2; }
} prefix[26][MAX_N], Thash[26], pow_h[MAX_N];

vector<int> ansbox;

hash_val getHash(int l, int r, int c)
{
    return prefix[c][r] - prefix[c][l - 1] * pow_h[r - l + 1];
}

int main()
{
    scanf("%d%d%s%s", &n, &m, S + 1, T + 1);
    pow_h[0] = hash_val{1, 1};
    for (int i = 1; i <= n; i++)
        pow_h[i] = pow_h[i - 1] * bitnum;
    for (int i = 0; i < 26; i++)
        prefix[i][0] = hash_val{0, 0};
    for (int i = 1; i <= n; i++)
    {
        for (int c = 0; c < 26; c++)
            prefix[c][i] = prefix[c][i - 1] * bitnum + (S[i] == (c + 'a')), last_ptr[c][i] = last_ptr[c][i - 1];
        last_ptr[S[i] - 'a'][i] = i;
    }
    for (int i = 1; i <= m; i++)
        for (int c = 0; c < 26; c++)
            Thash[c] = Thash[c] * bitnum + (T[i] == (c + 'a'));
    for (int i = 1; i + m - 1 <= n; i++)
    {
        int j = i + m - 1;
        bool flag = true;
        memset(vis, false, sizeof(vis));
        for (int c = 0; c < 26; c++)
            if (last_ptr[c][j] >= i && !vis[c])
            {
                int tc = T[last_ptr[c][j] - i + 1] - 'a';
                if (vis[tc])
                    flag = false;
                else if (!(getHash(i, j, c) == Thash[tc]))
                    flag = false;
                else if (!(getHash(i, j, tc) == Thash[c]))
                    flag = false;
                else
                    vis[c] = vis[tc] = true;
                if (!flag)
                    break;
            }
        if (flag)
            ansbox.push_back(i);
    }
    printf("%d\n", (int)ansbox.size());
    for (int i = 0, siz = ansbox.size(); i < siz; i++)
        printf("%d ", ansbox[i]);
    puts("");
    return 0;
}