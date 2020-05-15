// CF321E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4040, MAX_K = 808;

int n, k, mat[MAX_N][MAX_N], dp[MAX_K][MAX_N];

inline char nc()
{
    static char buffer[1 << 20], *p1 = buffer, *p2 = buffer;
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = nc();
    }
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return x * f;
}

int calc(int l, int r) { return mat[r][r] - mat[l - 1][r] - mat[r][l - 1] + mat[l - 1][l - 1]; }

void solve(int id, int l, int r, int L, int R)
{
    if (L > R || l > r)
        return;
    int mid = (l + r) >> 1, gpt = 0;
    for (int i = L; i <= R && i < mid; i++)
        if (dp[id][mid] > dp[id - 1][i] + calc(i + 1, mid))
            dp[id][mid] = dp[id - 1][i] + calc(i + 1, mid), gpt = i;
    solve(id, l, mid - 1, L, gpt), solve(id, mid + 1, r, gpt, R);
}

int main()
{
    n = read(), k = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mat[i][j] = mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1] + read();
    memset(dp, 0x3f, sizeof(dp)), dp[0][0] = 0;
    for (int i = 1; i <= k; i++)
        solve(i, 1, n, 0, n);
    printf("%d\n", dp[k][n] >> 1);
    return 0;
}