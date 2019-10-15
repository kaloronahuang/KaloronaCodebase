// P1303.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4020;

char tmp[MAX_N];

struct BigInt
{
    int digits[MAX_N], tot;

    void clear() { memset(digits, 0, sizeof(digits)); }

    void read()
    {
        scanf("%s", tmp + 1);
        clear(), tot = strlen(tmp + 1);
        for (int i = 0; i < tot; i++)
            digits[tot - i - 1] = tmp[i + 1] - '0';
    }

    void print()
    {
        int pos = 0;
        for (pos = MAX_N - 1; pos > 0; pos--)
            if (digits[pos] != 0)
                break;
        for (; pos >= 0; pos--)
            putchar(digits[pos] + '0');
        putchar('\n');
    }

    BigInt operator+(const BigInt &target)
    {
        BigInt ret;
        ret.clear();
        for (int i = 0; i < MAX_N - 1; i++)
        {
            ret.digits[i] += target.digits[i] + digits[i];
            if (ret.digits[i] >= 10)
                ret.digits[i + 1] += (ret.digits[i] / 10), ret.digits[i] %= 10;
        }
        return ret;
    }

    BigInt operator*(const BigInt &target)
    {
        BigInt ret;
        ret.clear();
        for (int i = 0; i < MAX_N - 1; i++)
        {
            for (int j = 0; j <= i; j++)
                ret.digits[i] += target.digits[j] * digits[i - j];
            if (ret.digits[i] >= 10)
                ret.digits[i + 1] += (ret.digits[i] / 10), ret.digits[i] %= 10;
        }
        return ret;
    }
};

int main()
{
    BigInt A, B;
    A.read(), B.read();
    (A * B).print();
    return 0;
}