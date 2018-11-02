// P2758.cpp
#include <iostream>

using namespace std;

string a, b;
const int maxn = 2100;
int F[maxn][maxn];
int n = 0;
/*
int DFS(int i, int j)
{
    if (a[i] == b[j])
        return DFS(i + 1, j + 1);
    else
        return min(DFS(i + 1, j) + 1, DFS(i + 1, j) + 1); // delete & insert;
}
*/
int main()
{
    cin >> a;
    cin >> b;
    int la = a.length();
    int lb = b.length();
    fill(F[0], F[0] + maxn * maxn, 0);
    for (int i = 0; i <= la; i++)
        F[i][0] = i;
    for (int i = 0; i <= lb; i++)
        F[0][i] = i;
    for (int i = 1; i <= la; i++)
        for (int j = 1; j <= lb; j++)
            if (a[i - 1] == b[j - 1])
                F[i][j] = F[i - 1][j - 1];
            else
                F[i][j] = min(F[i - 1][j], min(F[i][j - 1], F[i - 1][j - 1])) + 1;
    cout << F[la][lb];
    return 0;
}