// AGC040A.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 5e5 + 200;

ll n, acc, ans, seq[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%s", str + 1);
    n = strlen(str + 1);
    seq[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        acc = (str[i] == '<') ? acc + 1 : 0;
        seq[i + 1] = acc;
    }
    acc = 0;
    for (int i = n; i >= 1; i--)
    {
        acc = (str[i] == '>') ? acc + 1 : 0;
        seq[i] = max(seq[i], acc);
    }
    for (int i = 1; i <= n + 1; i++)
        ans += seq[i];
    printf("%lld", ans);
    return 0;
}