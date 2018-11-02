// P3146.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
int F[250][250];

void init()
{
    cin >> N;
    memset(F, 0, sizeof(F));
    for (int i = 0; i < N; i++)
        cin >> F[i][i];
}

int genDP()
{
    int res = -1;
    for (int l = N - 1; l >= 0; l--)
        for (int r = l + 1; r < N; r++)
            for (int k = l; k < r; k++)
                if (F[l][k] == F[k + 1][r])
                    F[l][r] = max(F[l][r], F[l][k] + 1), res = max(res, F[l][r]);
    return res;
}

int main()
{
    init();
    cout << genDP();
    return 0;
}