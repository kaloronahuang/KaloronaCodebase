// sequence.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 2020, mod = 1e9 + 7;

char tmp_buff[MAX_N], opt[MAX_N * 5];

struct BigInt
{
    int units[110];

    BigInt &operator=(const char *buff)
    {
        memset(units, 0, sizeof(units)), units[0] = 1;
        int n = strlen(buff), tmp = 1;
        for (int i = 1; i <= n; i++)
        {
            if (tmp == 10000)
                units[0]++, tmp = 1;
            units[units[0]] += tmp * (buff[n - i] - '0'), tmp *= 10;
        }
        return *this;
    }

    BigInt &operator=(long long nd)
    {
        sprintf(tmp_buff, "%lld", nd);
        return (*this = tmp_buff);
    }

    bool operator>(const BigInt &nd) const
    {
        if (nd.units[0] != units[0])
            return units[0] > nd.units[0];
        for (int i = units[0]; i >= 1; i--)
            if (units[i] != nd.units[i])
                return units[i] > nd.units[i];
        return false;
    }
    bool operator>=(const BigInt &nd) const { return !(nd > *this); }

    bool operator<(const BigInt &nd) const { return nd > *this; }
    bool operator<=(const BigInt &nd) const { return !(*this > nd); }

    bool operator!=(const BigInt &nd) const { return (nd > *this) || (*this > nd); }
    bool operator==(const BigInt &nd) const { return !((nd > *this) || (*this > nd)); }

    BigInt operator+(const BigInt &nd)
    {
        BigInt ret;
        ret.units[0] = max(units[0], nd.units[0]);
        for (int i = 1; i <= ret.units[0]; i++)
        {
            ret.units[i] += units[i] + nd.units[i];
            if (ret.units[i] >= 10000)
                ret.units[i] -= 10000, ret.units[i + 1]++;
        }
        if (ret.units[ret.units[0] + 1] > 0)
            ret.units[0]++;
        return ret;
    }

    BigInt operator+=(const BigInt &nd) { return *this = *this + nd; }

    BigInt operator-(const BigInt &nd)
    {
        BigInt ret;
        ret.units[0] = units[0];
        for (int i = 1; i <= ret.units[0]; i++)
        {
            ret.units[i] += units[i] - nd.units[i];
            if (ret.units[i] < 0)
                ret.units[i] += 10000, ret.units[i + 1]--;
        }
        while (ret.units[ret.units[0]] == 0 && ret.units[0] > 1)
            ret.units[0]--;
        return ret;
    }

    BigInt operator-=(const BigInt &nd) { return *this = *this - nd; }

    BigInt operator*(const BigInt &nd)
    {
        BigInt ret;
        ret.units[0] = nd.units[0] + units[0] + 1;
        for (int i = 1; i <= units[0]; i++)
            for (int j = 1; j <= nd.units[0]; j++)
            {
                ret.units[i + j - 1] += units[i] * nd.units[j];
                ret.units[i + j] += ret.units[i + j - 1] / 10000;
                ret.units[i + j] %= 10000;
            }
        while (ret.units[0] > 1 && ret.units[ret.units[0]] == 0)
            ret.units[0]--;
        return ret;
    }

    void output()
    {
        cout << units[units[0]];
        for (int i = units[0] - 1; i >= 1; i--)
            cout.width(4), cout.fill('0'), cout << units[i];
    }

    BigInt() { memset(units, 0, sizeof(units)), units[0] = 1; }
    BigInt(long long num) { *this = num; }
} pre_xor[MAX_N][MAX_N], suf_and[MAX_N][MAX_N];
int n, ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
    {
        pre_xor[i][ai[i]] = 1;
        for (int j = 0; j < 1024; j++)
            pre_xor[i][j] = (pre_xor[i][j] + pre_xor[i - 1][j ^ ai[i]]);
        for (int j = 0; j < 1024; j++)
            pre_xor[i][j] = (pre_xor[i][j] + pre_xor[i - 1][j]);
    }
    for (int i = n; i >= 1; i--)
    {
        suf_and[i][ai[i]] = 1;
        for (int j = 0; j < 1024; j++)
            suf_and[i][j & ai[i]] = (suf_and[i][j & ai[i]] + suf_and[i + 1][j]);
        for (int j = 0; j < 1024; j++)
            suf_and[i][j] = (suf_and[i][j] + suf_and[i + 1][j]);
    }
    BigInt ans = 0;
    for (int i = 2; i <= n; i++)
        for (int j = 0; j < 1024; j++)
            ans += pre_xor[i - 1][j] * (suf_and[i][j] - suf_and[i + 1][j]);
    ans.output();
    return 0;
}