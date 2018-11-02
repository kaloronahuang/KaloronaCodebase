// P1220.cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 60;
int n;
int sts;
int lightpos[maxn];
int walt[maxn];
int F[maxn][maxn][2];

void preDP()
{
    memset(F, 127, sizeof(F));
    F[sts][sts][0] = F[sts][sts][1] = 0;
    for (int j = sts; j <= n; j++)
        for (int i = j - 1; i > 0; i--)
            F[i][j][0] = min(F[i + 1][j][0] + (walt[n] - (walt[j] - walt[i])) * (lightpos[i + 1] - lightpos[i]),
                             F[i + 1][j][1] + (walt[n] - (walt[j] - walt[i])) * (lightpos[j] - lightpos[i])),
            F[i][j][1] = min(F[i][j - 1][1] + (walt[n] - (walt[j - 1] - walt[i - 1])) * (lightpos[j] - lightpos[j - 1]),
                             F[i][j - 1][0] + (walt[n] - (walt[j - 1] - walt[i - 1])) * (lightpos[j] - lightpos[i]));
}

int main()
{
    cin >> n >> sts;
    walt[0] = 0;
    for (int i = 1; i <= n; i++)
        cin >> lightpos[i] >> walt[i], walt[i] += walt[i - 1];
    preDP();
    cout << min(F[1][n][0], F[1][n][1]);
    return 0;
}