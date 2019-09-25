// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

inline int read()
{
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9')
        f = (ch == '-') ? -1 : f, ch = getchar();
    while ('0' <= ch && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}

const int MAX_N = 1e5 + 200;

int m, n, si[MAX_N], K, min_val, max_val, ptr;
ll a[MAX_N];

int main()
{
    m = read();
    for (int i = 1; i <= m; i++)
        si[i] = read();
    n = read();
    while (n--)
    {
        a[0] = read(), a[1] = read(), K = read();
        max_val = min_val = si[1];
        if (a[0] == 0 && a[1] == 0)
        {
            printf("%d %d\n", si[1], si[1]);
            continue;
        }
        for (ptr = 2; ptr <= 100 && abs(a[ptr] = 1LL * K * a[ptr - 1] + a[ptr - 2]) <= 1e14; ptr++)
            ;
        ptr--;
        for (int i = 1; i <= m && si[i] <= ptr; i++)
            min_val = (a[si[i]] < a[min_val]) ? si[i] : min_val, max_val = (a[si[i]] > a[max_val]) ? si[i] : max_val;
        if (si[m] > 100)
            if (a[ptr] < 0)
                min_val = si[m];
            else
                max_val = si[m];
        printf("%d %d\n", max_val, min_val);
    }
    return 0;
}