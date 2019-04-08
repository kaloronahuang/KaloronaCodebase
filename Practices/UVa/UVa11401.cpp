// UVa11401.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 10001000;
ll f[MAX_N], n;
int main()
{
    for (int i = 4; i < MAX_N; i++)
        f[i] = f[i - 1] + ((i - 1) * (i - 2) / 2 - (i - 1) / 2) / 2;
    while (cin >> n)
        if (n < 3)
            break;
        else
            printf("%lld\n", f[n]);
    return 0;
}