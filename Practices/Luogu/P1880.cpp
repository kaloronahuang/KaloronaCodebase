// P1880.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 210000000;
int n;
int arr[1110];
int d[1110];
int Fmax[1110][1110];
int Fmin[1110][1110];

void init()
{
    d[0] = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i], arr[i + n] = arr[i];
    for (int i = 1; i <= 2 * n; i++)
    {
        d[i] = d[i - 1] + arr[i];
        Fmin[i][i] = 0;
        Fmax[i][i] = 0;
        for (int j = i + 1; j <= 2 * n; j++)
            Fmin[i][j] = INF, Fmax[i][j] = 0;
    }
}

void genDP()
{
    for (int i = 1; i < 2 * n; i++)
        for (int j = i + 1; j <= 2 * n; j++)
            for (int k = i; k < j; k++)
                Fmax[i][j] = max(Fmax[i][j], Fmax[i][k] + Fmax[k + 1][j] + d[j] - d[i - 1]),
                Fmin[i][j] = min(Fmin[i][j], Fmin[i][k] + Fmin[k + 1][j] + d[j] - d[i - 1]);
}

void solve()
{
    init();
    genDP();
    int min_ans = INF;
    int max_ans = 0;
    for (int i = 1; i <= n; i++)
        min_ans = min(min_ans, Fmin[i][i + n - 1]),
        max_ans = max(max_ans, Fmax[i][i + n - 1]);
    cout << min_ans << endl
         << max_ans;
}

int main()
{
    solve();
    return 0;
}