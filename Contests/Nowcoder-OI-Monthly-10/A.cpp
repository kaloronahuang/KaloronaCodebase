// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 6e5 + 200;

char str[MAX_N];

int main()
{
    ll res;
    scanf("%lld%s", &res, str + 1);
    ll tmp = 0, len = strlen(str + 1);
    char opt = 0;
    str[len + 1] = '?';
    for (int i = 1; i <= len + 1; i++)
        if (!isdigit(str[i]))
        {
            if (opt == '*')
                res *= tmp;
            else if (opt == '+')
                res += tmp;
            else if (opt == '-')
                res -= tmp;
            else if (opt == '%')
                res %= tmp;
            else if (opt == '^')
                res <<= 1;
            opt = str[i], tmp = 0;
        }
        else
            tmp = tmp * 10 + str[i] - '0';
    printf("%lld", llabs(res));
    return 0;
}