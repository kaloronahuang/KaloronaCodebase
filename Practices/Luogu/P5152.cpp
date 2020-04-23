// P5152.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2550, MAX_Q = 50050, LOG = 30;

int n, q, nodes[4][MAX_N][MAX_N];
char cmdlet[20];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int y, int val)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
        {
            nodes[0][i][j] ^= val;
            nodes[1][i][j] ^= (y & 1) * val;
            nodes[2][i][j] ^= (x & 1) * val;
            nodes[3][i][j] ^= (x & 1) * (y & 1) * val;
        }
}

int query(int x, int y, int ret = 0)
{
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
        {
            ret ^= nodes[0][i][j] * ((x + 1) & (y + 1) & 1);
            ret ^= nodes[1][i][j] * ((x + 1) & 1);
            ret ^= nodes[2][i][j] * ((y + 1) & 1);
            ret ^= nodes[3][i][j];
        }
    return ret;
}

void output(int x)
{
    for (int i = 0; i < 30; i++)
        if (x & (1 << i))
            putchar('2');
        else
            putchar('1');
    putchar('\n');
}

int main()
{
    scanf("%d%d", &n, &q);
    while (q--)
    {
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'P')
        {
            int k = 0, cmd = 0, a, b, x, y;
            scanf("%d%d%d%d%d", &a, &b, &x, &y, &k);
            while (k--)
            {
                int id, val;
                scanf("%d%d", &id, &val);
                cmd ^= ((val & 1) << (id - 1));
            }
            update(a, b, cmd), update(x + 1, y + 1, cmd), update(x + 1, b, cmd), update(a, y + 1, cmd);
        }
        else
        {
            int a, b, x, y;
            scanf("%d%d%d%d", &a, &b, &x, &y);
            output(query(x, y) ^ query(a - 1, b - 1) ^ query(a - 1, y) ^ query(x, b - 1));
        }
    }
    return 0;
}