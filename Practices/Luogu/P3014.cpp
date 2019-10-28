// P3014.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 22;

int n, k, tmp[MAX_N];
ll fac[MAX_N], step;
bool vis[MAX_N];

char getOpt()
{
    char ch;
    while (!isupper(ch = getchar()))
        ;
    return ch;
}

int main()
{
    for (int i = fac[0] = 1; i <= 20; i++)
        fac[i] = fac[i - 1] * 1LL * i;
    scanf("%d%d", &n, &k);
    while (k--)
    {
        char opt = getOpt();
        if (opt == 'P')
        {
            // reverse expansion;
            memset(vis, false, sizeof(vis));
            scanf("%lld", &step), step--;
            for (int i = 1; i <= n; i++)
            {
                ll level = step / fac[n - i];
                step %= fac[n - i];
                for (int j = 1; j <= n; j++)
                    if (!vis[j])
                    {
                        if (level == 0)
                        {
                            printf("%d ", j), vis[j] = true;
                            break;
                        }
                        level--;
                    }
            }
            puts("");
        }
        else
        {
            ll ln = 0;
            for (int i = 1; i <= n; i++)
                scanf("%d", &tmp[i]);
            for (int i = 1, cnt = 0; i <= n; i++)
            {
                cnt = 0;
                for (int j = 1; j <= i; j++)
                    if (tmp[j] <= tmp[i])
                        cnt++;
                ln += fac[n - i] * (tmp[i] - cnt);
            }
            printf("%lld\n", ln + 1);
        }
    }
    return 0;
}