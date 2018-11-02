// P1855.cpp
#include <iostream>

using namespace std;

const int maxn = 120;
int n, M, T;
int mi[maxn], ti[maxn];
int F[maxn][250][250];

void DP()
{
    for (int i = 0; i <= M; i++)
        for (int t = 0; t <= T; t++)
            for (int tot = 1; tot <= n; tot++)
                if (i - mi[tot] >= 0 && t - ti[tot] >= 0)
                    F[tot][i][t] = max(F[tot - 1][i][t], F[tot - 1][i - mi[tot]][t - ti[tot]] + 1);
                else
                    F[tot][i][t] = F[tot - 1][i][t];
}

int main()
{
    cin >> n >> M >> T;
    for (int i = 1; i <= n; i++)
        cin >> mi[i] >> ti[i];
    DP();
    cout << F[n][M][T];
    return 0;
}