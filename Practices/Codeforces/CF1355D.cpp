// CF1355D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, S, ai[MAX_N];

int main()
{
    scanf("%d%d", &n, &S);
    ai[n] = S - (n - 1);
    for (int i = 1; i <= n - 1; i++)
        ai[i] = 1;
    if (ai[n] - 1 > n - 1)
    {
        puts("YES");
        for (int i = 1; i <= n; i++)
            printf("%d ", ai[i]);
        puts(""), printf("%d\n", ai[n] - 1);
    }
    else
        puts("NO");
    return 0;
}