// CH3401.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 70;
ll N, M, t, act;
char opt[MAX_N][MAX_N];
string opts[MAX_N];
struct matrix
{
    ll mat[MAX_N][MAX_N], n, m;
    matrix() { memset(mat, 0, sizeof(mat)); }
    matrix(int n, int m)
    {
        this->n = n, this->m = m;
        for (int i = 1; i <= max(n, m); i++)
            mat[i][i] = 1;
    }
    matrix operator*(const matrix &tar) const
    {
        matrix ans = matrix();
        ans.n = n, ans.m = tar.m;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= tar.m; j++)
                for (int k = 0; k <= m; k++)
                    ans.mat[i][j] += mat[i][k] * tar.mat[k][j];
        return ans;
    }
    matrix operator^(const int &tim) const
    {
        int ti = tim;
        matrix ans, bas = *this;
        for (int i = 0; i <= max(n, m); i++)
            ans.mat[i][i] = 1;
        ans.n = n, ans.m = m;
        while (ti)
        {
            if (ti & 1)
                ans = ans * bas;
            bas = bas * bas;
            ti >>= 1;
        }
        return ans;
    }
} P, Q, mats[70];
ll getPos(ll x, ll y) { return (x - 1) * M + y; }
int main()
{
    scanf("%lld%lld%lld%lld", &N, &M, &t, &act);
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> opt[i][j], opt[i][j] -= '0';
    for (int i = 0; i < act; i++)
        cin >> opts[i];
    int p = t / 60, q = t % 60;
    matrix F;
    F.n = 0, F.m = getPos(N, M), F.mat[0][0] = 1;
    for (int tim = 1; tim <= 60; tim++)
    {
        matrix current;
        current.n = getPos(N, M), current.m = getPos(N, M);
        current.mat[0][0] = 1;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
            {
                int pos = (tim - 1) % (opts[opt[i][j]].size());
                char op = opts[opt[i][j]][pos];
                switch (op)
                {
                case 'N':
                    if (i > 1)
                        current.mat[getPos(i, j)][getPos(i - 1, j)] = 1;
                    break;
                case 'S':
                    if (i < N)
                        current.mat[getPos(i, j)][getPos(i + 1, j)] = 1;
                    break;
                case 'E':
                    if (j < M)
                        current.mat[getPos(i, j)][getPos(i, j + 1)] = 1;
                    break;
                case 'W':
                    if (j > 1)
                        current.mat[getPos(i, j)][getPos(i, j - 1)] = 1;
                    break;
                case 'D':
                    break;
                default:
                    current.mat[0][getPos(i, j)] = op - '0';
                    current.mat[getPos(i, j)][getPos(i, j)] = 1;
                    break;
                }
            }
        mats[tim] = current;
    }
    P = mats[1];
    for (int i = 2; i <= 60; i++)
        P = P * mats[i];
    P = P ^ p;
    Q = q == 0 ? matrix(getPos(N, M), getPos(N, M)) : mats[1];
    for (int i = 2; i <= q; i++)
        Q = Q * mats[i];
    F = F * P * Q;
    ll ans = 0;
    for (int i = 1; i <= getPos(N, M); i++)
        ans = max(ans, F.mat[0][i]);
    printf("%lld", ans);
    return 0;
}