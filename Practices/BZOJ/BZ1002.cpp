// BZ1002.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

char buff[MAX_N];

struct BigInt
{
    int digits[MAX_N];

    void read(int number)
    {
        int ptr = 0;
        while (number)
            digits[ptr++] = number % 10, number /= 10;
    }

    void clear() { memset(digits, 0, sizeof(digits)); }

    BigInt operator*(const int &rhs)
    {
        BigInt ret;
        ret.clear();
        for (int i = 0; i < MAX_N - 1; i++)
            ret.digits[i] = digits[i] * rhs;
        for (int i = 0; i < MAX_N - 1; i++)
            ret.digits[i + 1] += ret.digits[i] / 10, ret.digits[i] %= 10;
        return ret;
    }

    BigInt operator-(const BigInt &rhs)
    {
        BigInt ret;
        ret.clear(), ret.digits[0] = 2;
        for (int i = 0; i < MAX_N - 1; i++)
        {
            ret.digits[i] += digits[i] - rhs.digits[i];
            if (ret.digits[i] < 0)
                ret.digits[i] += 10, ret.digits[i + 1]--;
        }
        return ret;
    }

    void output()
    {
        int ptr;
        for (ptr = MAX_N - 1; ptr > 0; ptr--)
            if (digits[ptr] != 0)
                break;
        for (; ptr >= 0; ptr--)
            putchar(digits[ptr] + '0');
        putchar('\n');
    }
} seq[MAX_N];

int main()
{
    int n;
    scanf("%d", &n);
    seq[1].read(1), seq[2].read(5);
    for (int i = 3; i <= n; i++)
        seq[i] = seq[i - 1] * 3 - seq[i - 2];
    seq[n].output();
    return 0;
}