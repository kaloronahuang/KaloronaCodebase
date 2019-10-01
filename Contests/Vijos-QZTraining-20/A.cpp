// A.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 10100;

ll seq[MAX_N], n, B[MAX_N], sol[MAX_N], cnt;

bool check()
{
    memset(B, 0, sizeof(B)), B[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j >= 1; j--)
            B[j] = B[j - 1] - B[j] * sol[i];
        B[0] = -B[0] * sol[i];
    }
    for (int i = 0; i <= n; i++)
        if (seq[i] != B[i])
            return false;
    return true;
}

void dfs(int pos)
{
    if (pos > n)
        if (check())
        {
            sort(sol + 1, sol + pos);
            for (int i = 1; i <= pos - 1; i++)
                printf("%d ", sol[i]);
            exit(0);
        }
        else
            return;
    else
        for (int i = 1; i <= cnt; i++)
        {
            sol[pos] = sol[i];
            dfs(pos + 1);
        }
}

int main()
{
    scanf("%lld", &n);
    for (int i = 0; i <= n; i++)
        scanf("%lld", &seq[i]);
    for (int i = 1; i <= 20; i++)
    {
        ll pans = 0;
        for (int j = n; j >= 0; j--)
            pans = pans * i + seq[j];
        if (pans == 0)
            sol[++cnt] = i;
    }
    dfs(cnt + 1);
    return 0;
}