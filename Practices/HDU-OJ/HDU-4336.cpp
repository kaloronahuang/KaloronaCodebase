// HDU-4336.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22, MAX_M = (1 << 20);

int n;
double pi[MAX_N], gans;

void dfs(int pos, double sum, int opt)
{
    if (pos == n + 1)
    {
        if (sum > 1e-9)
            gans += opt / sum;
        return;
    }
    dfs(pos + 1, sum + pi[pos], -opt);
    dfs(pos + 1, sum, opt);
}

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; i++)
            scanf("%lf", &pi[i]);
        gans = 0, dfs(1, 0, -1);
        printf("%.4lf\n", gans);
    }
    return 0;
}