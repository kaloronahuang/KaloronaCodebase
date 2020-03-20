// ARC102A.cpp
#include <bits/stdc++.h>

using namespace std;

int n, k;

int main()
{
    scanf("%d%d", &n, &k);
    long long ret = 0;
    if (k % 2 == 0)
    {
        k /= 2;
        int part1 = (n / k) / 2;
        int part2 = ((n / k) + 1) / 2;
        ret += 1LL * part1 * part1 * part1 + 1LL * part2 * part2 * part2;
    }
    else
        ret += 1LL * (n / k) * (n / k) * (n / k);

    printf("%lld\n", ret);
    return 0;
}