// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef long double ld;

int n;
ld pi[10], f[MAX_N][7], g[MAX_N][7], s[MAX_N][7];

void fileIO()
{
    freopen("dice.in", "r", stdin);
    freopen("dice.out", "w", stdout);
}

int main()
{
    // fileIO();
    for (int i = 1; i <= 6; i++)
        cin >> pi[i], f[1][i] = pi[i];
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= 6; j++)
            for (int k = 1; k <= 6; k++)
                if (j != k)
                    f[i][j] += f[i - 1][k] * ld(pi[j] / (1.0 - pi[k]));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 6; j++)
        {
            for (int k = 1; k <= 6; k++)
                if (j != k)
                    g[i][j] += g[i - 1][k] * ld(pi[j] / (1.0 - pi[k]));
            g[i][j] += f[i][j] * j;
        }
    ld ans1 = 0, ans2 = 0;
    for (int i = 1; i <= 6; i++)
        ans1 += g[n][i];

    ld tmp = ans1 / n;
    for (int i = 1; i <= 6; i++)
        f[1][i] = pi[i] * (i - tmp), g[1][i] = pi[i], s[1][i] = (i - tmp) * (i - tmp) * pi[i];
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= 6; j++)
        {
            f[i][j] = g[i][j] = 0;
            ld tmp_sum = 0;
            for (int k = 1; k <= 6; k++)
                if (j != k)
                {
                    f[i][j] += f[i - 1][k] * pi[j] / (1.0 - pi[k]), tmp_sum += 1.0 * pi[j] * g[i - 1][k] / (1 - pi[k]);
                    s[i][j] += s[i - 1][k] * ld(pi[j] / (1.0 - pi[k]));
                }
            s[i][j] += 2.0 * (j - tmp) * f[i][j] + tmp_sum * (j - tmp) * (j - tmp), f[i][j] += tmp_sum * (j - tmp);
            g[i][j] = tmp_sum;
        }
    for (int i = 1; i <= 6; i++)
        ans2 += s[n][i];
    printf("%.10Lf\n%.10Lf\n", ans1, ans2);
    return 0;
}