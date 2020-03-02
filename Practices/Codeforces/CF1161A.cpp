// CF1161A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, INF = 0x3f3f3f3f;

int n, k, min_val[MAX_N], max_val[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        min_val[i] = INF, max_val[i] = -1;
    for (int i = 1, val; i <= k; i++)
        scanf("%d", &val), min_val[val] = min(min_val[val], i), max_val[val] = max(max_val[val], i);

    int gans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (max_val[i] == -1)
            gans++;
        if (i != 1 && (max_val[i - 1] == -1 || max_val[i] < min_val[i - 1]))
            gans++;
        if (i != n && (max_val[i + 1] == -1 || max_val[i] < min_val[i + 1]))
            gans++;
    }

    printf("%d\n", gans);
    return 0;
}