// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_Q = 6, MAX_R = 21;
const double eps = 1e-8;

int N, R, Q, mat_siz, stat_siz, mapper[MAX_Q][MAX_R];
ll S;

struct matrix
{
    double mat[155][155];

    void clear() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &target) const
    {
        matrix ans;
        ans.clear();
        for (int i = 1; i <= mat_siz; i++)
            for (int j = 1; j <= mat_siz; j++)
                for (int k = 1; k <= mat_siz; k++)
                    ans.mat[i][j] += mat[i][k] * target.mat[k][j];
        return ans;
    }
} f, a1, a2, b;

double DP(double p)
{
    f.clear(), a1.clear(), a1.clear();
    for (int lives = 1; lives <= Q; lives++)
        for (int conseq = 0; conseq <= R; conseq++)
            if (lives >= conseq || lives == Q)
            {
                a1.mat[mapper[lives][conseq]][mapper[min(lives + 1, Q)][min(conseq + 1, R)]] = p;
                a1.mat[mapper[lives][conseq]][mapper[lives - 1][0]] = 1.0 - p;
            }
    a1.mat[stat_siz][stat_siz] = 1;
    for (int lives = 0; lives <= Q; lives++)
        for (int conseq = 0; conseq <= R; conseq++)
            if (lives >= conseq || lives == Q)
                a2.mat[mapper[lives][conseq]][stat_siz] = conseq;
    for (int i = 1; i <= mat_siz; i++)
        a2.mat[i][i] = 1;
    b = a1 * a2;
    f.mat[1][mapper[Q][0]] = 1;
    int tim = N;
    while (tim)
    {
        if (tim & 1)
            f = f * b;
        b = b * b;
        tim >>= 1;
    }
    return f.mat[1][stat_siz];
}

int main()
{
    scanf("%d%d%d%lld", &N, &R, &Q, &S);
    // zip the status up!
    for (int lives = 0; lives <= Q; lives++)
        for (int conseq = 0; conseq <= R; conseq++)
            if (lives >= conseq || lives == Q)
                mapper[lives][conseq] = ++stat_siz;
    // as the end status;
    ++stat_siz, mat_siz = stat_siz;
    if (DP(1.0) <= S)
        puts("Impossible.");
    else
    {
        double l = 0, r = 1.0;
        while (l < r - eps)
        {
            double mid = (l + r) / 2;
            if (DP(mid) > S)
                r = mid;
            else
                l = mid;
        }
        printf("%.6lf", l);
    }
    return 0;
}