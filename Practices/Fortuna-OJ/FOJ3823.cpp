// FOJ3823.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 33, mod = 1e9 + 7;

int n, ai[MAX_N][MAX_N], f[5500][MAX_N][MAX_N], matrix[5500][MAX_N * MAX_N];
vector<int> primes;

int id(int x, int y) { return n * (x - 1) + y; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &ai[i][j]);
            int x = ai[i][j];
            for (int k = 2; 1LL * k * k <= x; k++)
                if (x % k == 0)
                {
                    primes.push_back(k);
                    while (x % k == 0)
                        x /= k;
                }
            if (x > 1)
                primes.push_back(x);
        }
    sort(primes.begin(), primes.end()), primes.erase(unique(primes.begin(), primes.end()), primes.end());
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            int x = ai[i][j];
            for (int k = 1, siz = primes.size(); k <= siz; k++)
                while (x % primes[k - 1] == 0)
                    x /= primes[k - 1], f[k][i][j] ^= 1;
        }
    // construct the matrix;
    for (int i = 1; i <= n; i++)
    {
        matrix[i][0] = 1;
        for (int j = 1; j <= n; j++)
            matrix[i][id(i, j)] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        matrix[n + i][0] = 1;
        for (int j = 1; j <= n; j++)
            matrix[i + n][id(j, i)] = 1;
    }
    int caseTot = (n << 1);
    for (int i = 1, siz = primes.size(); i <= siz; i++)
    {
        matrix[++caseTot][0] = 0;
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= n; y++)
                matrix[caseTot][id(x, y)] = f[i][x][y];
    }
    // start to work
    int ans = 1, empty_slot = 0, pos = 1;
    for (int i = 1; i <= n * n; i++)
    {
        bool flag = false;
        for (int j = pos; j <= caseTot; j++)
            if (matrix[j][i])
            {
                swap(matrix[pos], matrix[j]), flag = true;
                break;
            }
        if (!flag)
            empty_slot++;
        else
            pos++;
        for (int j = pos; j <= caseTot; j++)
            if (matrix[j][i])
                for (int k = 0; k <= n * n; k++)
                    matrix[j][k] ^= matrix[pos - 1][k];
    }
    for (int i = 1; i <= caseTot; i++)
    {
        bool flag = false;
        for (int j = 1; j <= n * n; j++)
            if (matrix[i][j])
            {
                flag = true;
                break;
            }
        if (flag)
            continue;
        if (matrix[i][0])
            ans = 0;
    }
    for (int i = 1; i <= empty_slot; i++)
        ans = 2LL * ans % mod;
    printf("%d\n", ans);
    return 0;
}