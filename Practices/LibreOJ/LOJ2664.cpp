// LOJ2664.cpp
#include <bits/stdc++.h>

using namespace std;

inline char nc()
{
    static char buff[1 << 20], *p1 = buff, *p2 = buff;
    return p1 == p2 && (p2 = (p1 = buff) + fread(buff, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

const int MAX_N = 100005, MAX_D = 101;

int n, d, k, xi[MAX_N][MAX_D], B[MAX_N], B2[MAX_D], B3[MAX_D][MAX_D];

int calc(int x)
{
    int ret = 0;
    if (k == 2)
        for (int i = 1; i <= d; B2[i] ^= xi[x][i], i++)
            ret ^= B2[i] & xi[x][i];
    else
        for (int i = 1; i <= d; i++)
            for (int j = 1; j <= d; j++, B3[i][j] += xi[x][i] * xi[x][j], j++)
                ret += B3[i][j] * xi[x][i] * xi[x][j];
    return ret % k;
}

bool check(int idx1, int idx2)
{
    int ret = 0;
    for (int i = 1; i <= d; i++)
        ret = (0LL + ret + 1LL * xi[idx1][i] * xi[idx2][i] % k) % k;
    return ret % k == 0;
}

int main()
{
    n = read(), d = read(), k = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= d; j++)
            xi[i][j] = read() % k;
    srand(114514);
    // try!
    int caseTot = 7 - k;
    for (int i = 1; i <= n; i++)
        B[i] = i;
    while (caseTot--)
    {
        if (k == 2)
            memset(B2, 0, sizeof(B2));
        else
            memset(B3, 0, sizeof(B3));
        for (int i =2; i <= n; i++)
            swap(B[i], B[(rand() % (i - 1) + 1)]);
        for (int i = 1; i <= n; i++)
            if (calc(B[i]) != (i - 1) % k)
                for (int j = 1; j < i; j++)
                    if (check(B[i], B[j]))
                    {
                        if (B[i] > B[j])
                            swap(i, j);
                        printf("%d %d\n", B[i], B[j]), exit(0);
                    }
    }
    puts("-1 -1");
    return 0;
}