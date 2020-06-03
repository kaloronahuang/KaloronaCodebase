// ARC091A.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    if (n > m)
        swap(n, m);
    if (n == 1)
    {
        if (m == 1)
            puts("1");
        else
            printf("%d\n", max(0, m - 2));
        return 0;
    }
    printf("%lld\n", max(0LL, 1LL * (n - 2) * (m - 2)));
    return 0;
}