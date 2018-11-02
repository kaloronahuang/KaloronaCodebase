// P1070.cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 2020;
int table[maxn][maxn];
int cost[maxn];
int F[maxn];
int n, m, p;

int main()
{
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> table[i][j];
    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    fill(F, F + maxn, -(1e9));
    F[0] = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            int curt = j - 1;
            if (curt == 0)
                curt = n;
            int sum = table[curt][i];
            for (int k = 1; k <= p; k++)
            {
                if (i - k < 0)
                    break;
                F[i] = max(F[i], F[i - k] + sum - cost[curt]);
                curt--;
                if (curt == 0)
                    curt = n;
                sum += table[curt][i - k];
            }
        }
    cout << F[m];
    return 0;
}