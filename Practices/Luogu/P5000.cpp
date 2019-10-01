// P5000.cpp
#include <bits/stdc++.h>

using namespace std;

const int LEN = 1205;

struct BigInt
{
    int bits[LEN];

    void clear() { memset(bits, 0, sizeof(bits)); }

    BigInt() { clear(); }

    BigInt(int num)
    {
        clear();
        int cur = 0;
        while (num)
            bits[cur++] = num % 10, num /= 10;
    }

    BigInt operator*(const int &target)
    {
        BigInt ret;
        for (int i = 0; i < LEN - 1; i++)
        {
            ret.bits[i] += bits[i] * target;
            if (ret.bits[i] >= 10)
                ret.bits[i + 1] = ret.bits[i] / 10, ret.bits[i] %= 10;
        }
        return ret;
    }

    void print()
    {
        int pos;
        for (pos = LEN - 1; pos >= 1; pos--)
            if (bits[pos] != 0)
                break;
        for (; pos >= 0; pos--)
            putchar(bits[pos] + '0');
    }
};

const int MAX_N = 660;

int n, R, lenth;
char str[MAX_N];

int main()
{
    scanf("%d%d", &n, &R);
    while (n--)
    {
        scanf("%s", str + 1), lenth = strlen(str + 1);
        BigInt ans(1);
        for (int i = 1; i <= lenth; i++)
            str[i] = ((str[i] - 'A') + R) % 26 + 'A', ans = ans * str[i];
        printf("%s\n", str + 1);
        ans.print(), puts("");
    }
    return 0;
}