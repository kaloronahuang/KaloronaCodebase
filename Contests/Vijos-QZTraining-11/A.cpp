// A.cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, prefix, suffix;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, p; i <= n; i++)
        scanf("%d", &p), prefix += p - 1, suffix += m - p;
    printf("%d\n%d\n", max(1, m - suffix), min(m, prefix + 1));
    return 0;
}