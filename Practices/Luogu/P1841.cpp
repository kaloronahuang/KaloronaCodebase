// P1841.cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define ll long long
ll mat[300][300];
int dp[300][300];
bool ans[500];
const ll INF = (ll)(0x7fffffff) / 3;
int n, m;

void floyed()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (i != k)
                for (int j = 1; j <= n; j++)
                    if (i != j && j != k)
                        if (mat[i][k] + mat[k][j] < mat[i][j])
                            mat[i][j] = mat[i][k] + mat[k][j], dp[i][j] = k;
                        else if (mat[i][k] + mat[k][j] == mat[i][j])
                            dp[i][j] = -1;
}

void addpath(int src, int dst, ll w)
{
    mat[src][dst] = mat[dst][src] = w;
}

int main()
{
    fill(mat[0], mat[0] + 300 * 300, INF);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        addpath(a, b, c);
    }
    floyed();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (dp[i][j] != -1)
                ans[dp[i][j]] = true;
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (ans[i])
            cout << i << " ", flag = false;
    if (flag)
        cout << "No important cities.";
    return 0;
}