// P1040.cpp
#include <iostream>
#include <cstring>

using namespace std;
const int maxn = 50;
int n;
int di[maxn];
int F[maxn][maxn];
int root[maxn][maxn];

void preDP()
{
    for (int len = 2; len <= n; len++)
        for (int i = 0; i + len - 1 < n; i++)
            for (int k = i; k <= i + len - 1; k++)
            {
                int j = i + len - 1;
                // set k the root;
                int factor1 = (k - 1 < i) ? 1 : F[i][k - 1];
                int factor2 = (j < k + 1) ? 1 : F[k + 1][j];
                int ans = factor1 * factor2 + di[k];
                if (ans > F[i][j])
                    root[i][j] = k, F[i][j] = ans;
            }
}

void DFSPrint(int l, int r)
{
    int curt = root[l][r];
    int left = (curt - 1 < l) ? -1 : root[l][curt - 1];
    int right = (curt + 1 > r) ? -1 : root[curt + 1][r];
    cout << curt + 1 << " ";
    if (l == r)
        return;
    if (left != -1)
        DFSPrint(l, curt - 1);
    if (right != -1)
        DFSPrint(curt + 1, r);
}

int main()
{
    memset(F, 0, sizeof(F));
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> di[i], F[i][i] = di[i];
        root[i][i] = i;
    }
    preDP();
    cout << F[0][n - 1] << endl;
    DFSPrint(0, n - 1);
    return 0;
}