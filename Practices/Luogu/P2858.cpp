// P2858.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int F[2020][2020];
int a[2020];

void init()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> a[i], F[i][i] = a[i] * N;
}

void print()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
            cout << F[i][j] << " ";
        cout << endl;
    }
}

int genDP()
{
    for (int len = 2; len <= N; len++)
        for (int l = 1; l + len - 1 <= N; l++)
        {
            int r = l + len - 1;
            F[l][r] = max(F[l + 1][r] + a[l] * (N - len + 1), F[l][r - 1] + a[r] * (N - len + 1));
        }
    return F[1][N];
}

int main()
{
    init();
    cout << genDP();
    return 0;
}