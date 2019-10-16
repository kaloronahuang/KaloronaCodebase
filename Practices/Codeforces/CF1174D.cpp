// CF1174D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1 << 18) + 200;

int n, x, seq[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d%d", &n, &x);
    if (x >= (1 << n))
    {
        int len = (1 << n) - 1;
        printf("%d\n", len);
        for (int i = 1; i <= len; i++)
            printf("%d ", i ^ (i - 1));
    }
    else
    {
        vis[x] = true;
        int tot = 0;
        for (int i = 1, last = 0; i < (1 << n); i++)
            if (vis[i] == false)
                vis[i ^ x] = true, seq[++tot] = i ^ last, last = i;
        printf("%d\n", tot);
        for (int i = 1; i <= tot; i++)
            printf("%d ", seq[i]);
    }
    return 0;
}