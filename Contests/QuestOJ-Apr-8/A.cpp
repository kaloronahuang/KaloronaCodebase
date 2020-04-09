// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, base = 133;

typedef unsigned long long ull;

int T, n;
ull basepow[MAX_N], posHash[MAX_N], revHash[MAX_N];
char str[MAX_N];

ull getPosHash(int l, int r) { return posHash[r] - posHash[l - 1] * basepow[r - l + 1]; }

ull getRevHash(int l, int r) { return revHash[l] - revHash[r + 1] * basepow[r - l + 1]; }

int main()
{
    scanf("%d", &T), basepow[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        basepow[i] = basepow[i - 1] * base;
    while (T--)
    {
        scanf("%d%s", &n, str + 1);
        for (int i = 1; i <= n; i++)
            posHash[i] = posHash[i - 1] * base + str[i] - 'a';
        revHash[n + 1] = 0;
        for (int i = n; i >= 1; i--)
            revHash[i] = revHash[i + 1] * base + str[i] - 'a';
        if (posHash[n] != revHash[1])
            puts("1");
        else
        {
            bool flag = true;
            for (int i = 1; i <= n; i++)
                flag &= (getPosHash(1, i) == getRevHash(1, i)) || (getPosHash(i + 1, n) == getRevHash(i + 1, n));
            if (flag)
                puts("-1");
            else
                puts("2");
        }
    }
    return 0;
}