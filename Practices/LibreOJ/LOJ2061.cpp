// LOJ2061.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5005;

char tmp_buff[MAX_N];

struct BigInt
{
    int digits[MAX_N];

    void clear() { memset(digits, 0, sizeof(digits)); }

    BigInt &operator=(const char *buff)
    {
        memset(digits, 0, sizeof(digits)), digits[0] = 1;
        int len = strlen(buff);
        for (int i = len - 1; i >= 0; i--)
            digits[len - i - 1] = buff[i] - '0';
        return *this;
    }

    BigInt &operator=(long long nd)
    {
        sprintf(tmp_buff, "%lld", nd);
        return (*this = tmp_buff);
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
} D[200];

int n;

int main()
{
    scanf("%d", &n);
    if (n == 1 || n == 2)
        return printf("%d\n", n - 1), 0;
    D[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        BigInt t;
        t= i - 1;
        D[i] = t * (D[i - 1] + D[i - 2]);
    }
    D[n].print();
    return 0;
}