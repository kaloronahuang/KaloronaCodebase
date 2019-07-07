// D1.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 2000;

int n, deg[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, tmpx, tmpy; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), deg[tmpx]++, deg[tmpy]++;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 2)
            puts("NO"), exit(0);
    puts("YES");
    return 0;
}