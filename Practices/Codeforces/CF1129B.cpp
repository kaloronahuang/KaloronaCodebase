// CF1129B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int diff, limit = 1e6, n, len, seq[MAX_N], sum;

int main()
{
    scanf("%d", &diff);
    len = (diff & 1) ? 1997 : 1998, n = len + 2, sum = (diff + n) >> 1;
    seq[1] = 0, seq[2] = -1;
    for (int i = 3; i <= n; i++)
    {
        if (sum > limit)
            seq[i] = limit, sum -= limit;
        else
            seq[i] = sum, sum = 0;
    }
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("%d ", seq[i]);
    return 0;
}