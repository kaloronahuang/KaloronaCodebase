// BZ1005.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10000;

int di[MAX_N], n;

struct BigInt
{
    int digits[MAX_N];

    void clear() { memset(digits, 0, sizeof(digits)); }

    BigInt operator*(const int &rhs)
    {
        BigInt ret;
        ret.clear();
        for (int i = 1; i < MAX_N - 1; i++)
            ret.digits[i] = digits[i] * rhs;
        for (int i = 1; i < MAX_N - 1; i++)
            ret.digits[i + 1] += ret.digits[i] / 10, ret.digits[i] %= 10;
        return ret;
    }

    BigInt operator/(const int &rhs)
    {
        BigInt ret = *this;
        for (int i = MAX_N - 1; i >= 1; i--)
        {
            ret.digits[i - 1] += ret.digits[i] % rhs * 10;
            ret.digits[i] /= rhs;
        }
        return ret;
    }

    void output()
    {
        int ptr;
        for (ptr = MAX_N - 1; ptr >= 2; ptr--)
            if (digits[ptr] != 0)
                break;
        for (; ptr >= 1; ptr--)
            putchar(digits[ptr] + '0');
        putchar('\n');
    }
};

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &di[i]);
    int S = 0, siz = 0;
    for (int i = 1; i <= n; i++)
        if (di[i] == 0)
            puts("0"), exit(0);
        else if (di[i] != -1)
            S += di[i] - 1, siz++;
    BigInt ans;
    ans.clear(), ans.digits[1] = 1;
    for (int i = n - 2 - S + 1; i <= n - 2; i++)
        ans = ans * i;
    for (int i = 1; i <= n; i++)
        if (di[i] != -1)
            for (int j = 1; j <= di[i] - 1; j++)
                ans = ans / j;
    for (int i = 1; i <= n - S - 2; i++)
        ans = ans * (n - siz);
    ans.output();
    return 0;
}