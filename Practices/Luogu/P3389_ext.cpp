// P3389_ext.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, eps = 1e-8;

int n;
double ai[MAX_N][MAX_N];

void gauss()
{
    for (int i = 1; i <= n; i++)
    {
        int max_id = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(ai[j][i]) > fabs(ai[max_id][i]))
                max_id = j;
        for (int j = 1; j <= n + 1; j++)
            swap(ai[i][j], ai[max_id][j]);
        if (!ai[i][i])
            puts("No Solution"), exit(0);
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                double rate = ai[j][i] / ai[i][i];
                for (int k = i + 1; k <= n + 1; k++)
                    ai[j][k] -= ai[i][k] * rate;
            }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            scanf("%lf", &ai[i][j]);
    gauss();
    for (int i = 1; i <= n; i++)
        printf("%.2lf\n", ai[i][n + 1] / ai[i][i]);
    return 0;
}