// P1279.cpp
#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 2020;
int F[maxn][maxn];
string a, b;
int k;
int lena, lenb;

void DP()
{
    int lena = a.size();
    int lenb = b.size();
    for (int i = 1; i <= lena; i++)
        for (int j = 1; j <= lenb; j++)
            F[i][j] = min(min(F[i - 1][j] + k, F[i][j - 1] + k), F[i - 1][j - 1] + abs(a[i - 1] - b[j - 1]));
}

void preDP()
{
    lena = a.size();
    lenb = b.size();
    for (int i = 1; i <= lena; i++)
        F[i][0] = i * k;
    for (int i = 1; i <= lenb; i++)
        F[0][i] = i * k;
}

int main()
{
    getline(cin, a);
    getline(cin, b);
    cin >> k;
    fill(F[0], F[0] + maxn * maxn, 0);
    preDP();
    DP();
    cout << F[lena][lenb];
    return 0;
}