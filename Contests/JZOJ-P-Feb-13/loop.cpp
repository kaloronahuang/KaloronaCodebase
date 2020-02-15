// loop.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200, bitnum = 133;

typedef unsigned long long ull;

int n;
bool ans[MAX_N];
char str[MAX_N];
ull pre[MAX_N], pw[MAX_N];

void fileIO()
{
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
}

ull getHash(int l, int r) { return pre[r] - pre[l - 1] * pw[r - l + 1]; }

void solve(int l, int r)
{
    if (r - l + 1 == 2 && str[l] == str[r])
        return;
    for (int k = 1; k <= min(n, r - l + 1); k++)
        ans[k] |= (getHash(l, r - k + 1) != getHash(l + k - 1, r));
}

int main()
{
    // fileIO();
    for (int i = pw[0] = 1; i < MAX_N; i++)
        pw[i] = pw[i - 1] * bitnum;
    while (scanf("%s", str + 1) != EOF)
    {
        memset(ans, 0, sizeof(ans));
        n = strlen(str + 1);
        for (int i = 1; i <= n; i++)
            str[i + n] = str[i];
        for (int i = 1; i <= (n << 1); i++)
            pre[i] = pre[i - 1] * bitnum + str[i] - 'a' + 1;
        str[(n << 1) | 1] = str[n << 1];
        for (int i = 2, last_pt = 1; i <= (n << 1) + 1; i++)
            if (str[i] == str[i - 1])
                solve(last_pt, i - 1), last_pt = i;
        for (int i = 1; i <= n; i++)
            printf(ans[n - i + 1] ? "1" : "0");
        puts("");
    }
    return 0;
}