// P3389.cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int maxn = 200;
double mat[maxn][maxn];
bool flag = false;
int n;

void Solve()
{
    for (int i = 1; i <= n; i++)
    {
        int post = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(mat[post][i]) < fabs(mat[j][i]))
                post = j;
        if (post != i)
            swap(mat[post], mat[i]);
        for (int k = i + 1; k <= n; k++)
        {
            if (flag = (mat[i][i] == 0))
                return;
            double f = mat[k][i] / mat[i][i];
            for (int j = i; j <= n + 1; j++)
                mat[k][j] -= f * mat[i][j];
        }
    }
    for (int i = n; i > 0; i--)
    {
        for (int j = i + 1; j <= n; j++)
            mat[i][n + 1] -= mat[j][n + 1] * mat[i][j];
        if (flag = (mat[i][i] == 0))
            return;
        mat[i][n + 1] /= mat[i][i];
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++)
            cin >> mat[i][j];
    Solve();
    if (flag)
    {
        cout << "No Solution";
        return 0;
    }
    for (int i = 1; i <= n; i++)
        cout << fixed << setprecision(2) << mat[i][n + 1] << endl;
    return 0;
}