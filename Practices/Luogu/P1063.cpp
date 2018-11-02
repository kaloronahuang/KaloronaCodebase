// P1063.cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
const int maxn = 1005;
int w[maxn];
int F[1010][1010];

void init()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i], w[i + n] = w[i];
    memset(F, 0, sizeof(F));
}

void generateDP()
{
    for (int i = 2 * n - 1; i > 0; i--)
        for (int j = i + 1; j <= 2 * n; j++)
            for (int k = i; k < j; k++)
                F[i][j] = max((int)F[i][j], F[i][k] + F[k + 1][j] + (w[i] * w[k + 1] * w[j + 1]));
}

void solve()
{
    int max_ans = -1;
    for (int i = 1; i <= n; i++)
        max_ans = max(max_ans, F[i][i + n - 1]);
    cout << max_ans;
}

int main()
{
    init();
    generateDP();
    solve();
    return 0;
}