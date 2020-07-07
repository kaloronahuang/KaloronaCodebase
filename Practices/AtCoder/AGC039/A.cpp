// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, k;
char str[MAX_N], T[MAX_N];

int main()
{
    scanf("%s%d", str + 1, &k), n = strlen(str + 1);
    memcpy(T, str, sizeof(T));
    int scnt = 0;
    for (int i = 1; i < n; i++)
        if (str[i] == str[i + 1])
            scnt++, str[i + 1] = '$';
    int tcnt = 1;
    T[1] = '$';
    for (int i = 1; i < n; i++)
        if (T[i + 1] == T[i])
            tcnt++, T[i + 1] = '$';
    if (str[1] != str[n])
        printf("%lld\n", 1LL * scnt * k);
    else if (str[1] != T[n])
        printf("%lld\n", 1LL * (tcnt + scnt) * (k >> 1) + 1LL * (k & 1) * scnt);
    else
        printf("%lld\n", scnt + 1LL * (k - 1) * tcnt);
    return 0;
}