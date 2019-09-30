// COGS450.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e6 + 200;

ll n, seq[MAX_N], q[MAX_N], head, tail;

void setFileIO()
{
    freopen("smallblack.in", "r", stdin);
    freopen("smallblack.out", "w", stdout);
}

int main()
{
    setFileIO();
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &seq[i]);
    head = 1, tail = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head <= tail && seq[q[tail]] >= seq[i])
            tail--;
        if (head <= tail)
            printf("%lld ", seq[q[tail]]);
        else
            printf("%lld ", 0);
        while (head <= tail && seq[q[tail]] >= seq[i])
            tail--;
        q[++tail] = i;
    }
    return 0;
}