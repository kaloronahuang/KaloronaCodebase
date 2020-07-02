// CF461E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int m, ch[MAX_N * 20][4], calc[4][4][20], ptot, mlen;
ll n;
bool tag[MAX_N * 20];
char str[MAX_N];

ll fpow(ll bas, ll tim)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret *= bas;
        bas *= bas;
        tim >>= 1;
    }
    return ret;
}

struct matrix
{
    ll mat[4][4];
    ll *operator[](const int &rhs) { return mat[rhs]; }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        memset(ret.mat, 0x3f, sizeof(ret.mat));
        for (int k = 0; k < 4; k++)
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    ret[i][j] = min(ret[i][j], mat[i][k] + rhs.mat[k][j]);
        return ret;
    }
    matrix operator^(const ll &rhs)
    {
        ll tim = rhs - 1;
        matrix ret = *this, bas = *this;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} trans;

void insert(int start_pos)
{
    int p = 0, sc = str[start_pos] - 'A';
    for (int i = start_pos; i <= min(start_pos + mlen - 1, m); i++)
    {
        int c = str[i] - 'A';
        if (ch[p][c] == 0)
            ch[p][c] = ++ptot;
        p = ch[p][c];
        if (!tag[p])
            tag[p] = true, calc[sc][c][i - start_pos + 1]++;
    }
}

bool check(ll mid)
{
    matrix ret = trans ^ mid;
    bool flag = true;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            flag &= ret[i][j] >= n;
    return flag;
}

int main()
{
    scanf("%lld%s", &n, str + 1), m = strlen(str + 1), mlen = min(11, m + 1);
    for (int i = 1; i <= m; i++)
        insert(i);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = mlen; k >= 2; k--)
                if (calc[i][j][k] != fpow(4, k - 2))
                    trans[i][j] = k - 1;
    ll l = 1, r = n, res = 0;
    while (l <= r)
    {
        ll mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%lld\n", res);
    return 0;
}