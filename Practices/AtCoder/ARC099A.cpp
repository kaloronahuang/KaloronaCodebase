// ARC099A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, k, ai[MAX_N], pos[MAX_N];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    printf("%d\n", int(ceil(1.0 * (n - k) / (k - 1)) + 1));
    return 0;
}