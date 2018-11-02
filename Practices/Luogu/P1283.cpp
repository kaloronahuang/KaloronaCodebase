// P1283.cpp
#include <iostream>

using namespace std;
const int maxn = 50;
int n, ni[maxn];
int F[maxn][maxn];

void DP()
{
    for (int i = 1; i <= n; i++)
        for (int j = i; n - i - j > 0; j++)
        {
            int z = n - i - j;
            F[i][j] = 
        }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> ni[i];
}