// P1054.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 1e9 + 7, MAX_N = 30, INF = 0x3f3f3f3f;

int lens[MAX_N], n, val[MAX_N], tmp;
char str[MAX_N][60];

ll quick_pow(ll bas, int tim)
{
    ll ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

ll calc(char *str, int l, int r, ll x)
{
    int priority = 0, mnpos = 60, mn = INF, cnt = 0, p[60], num = 0;
    memset(p, 0x3f, sizeof(p));
    for (int i = r; i >= l; i--)
    {
        if (str[i] == ')')
            priority += 100;
        if (str[i] == '(')
            priority -= 100;
        if (str[i] == '^')
            p[i] = priority + 3, cnt++;
        if (str[i] == '*')
            p[i] = priority + 2, cnt++;
        if (str[i] == '+')
            p[i] = priority + 1, cnt++;
        if (str[i] == '-')
            p[i] = priority + 1, cnt++;
        if (mn > p[i])
            mn = p[i], mnpos = i;
    }
    if (cnt == 0)
    {
        for (int i = l; i <= r; i++)
            if (str[i] == 'a')
                return x;
        for (int i = l; i <= r; i++)
            if (isdigit(str[i]))
                num = num * 10 + str[i] - '0';
        return num;
    }
    if (str[mnpos] == '^')
        return quick_pow(calc(str, l, mnpos - 1, x), calc(str, mnpos + 1, r, x));
    if (str[mnpos] == '*')
        return 1LL * calc(str, l, mnpos - 1, x) * calc(str, mnpos + 1, r, x) % mod;
    if (str[mnpos] == '+')
        return (calc(str, l, mnpos - 1, x) + calc(str, mnpos + 1, r, x)) % mod;
    if (str[mnpos] == '-')
        return (calc(str, l, mnpos - 1, x) - calc(str, mnpos + 1, r, x)) % mod;
    return 0;
}

int main()
{
    scanf("%[^\r]", str[0]), getchar(), lens[0] = strlen(str[0]);
    scanf("%d", &n), getchar();
    for (int i = 1; i <= n; i++)
        scanf("%[^\r]", str[i]), getchar(), lens[i] = strlen(str[i]);
    for (int i = 0; i <= 10; i++)
        val[i] = calc(str[0], 0, lens[0] - 1, i - 5);
    for (int i = 1; i <= n; i++)
    {
        bool flag = true;
        for (int j = 0; j <= 10; j++)
            if (val[j] != calc(str[i], 0, lens[i] - 1, j - 5))
            {
                flag = false;
                break;
            }
        if (flag)
            printf("%c", 'A' + i - 1);
    }
    return 0;
}