// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, series[12] = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292};

int main()
{
    int n;
    scanf("%d", &n);
    if (n <= 11)
        printf("%d\n", series[n]);
    else
        printf("%lld\n", series[11] + 1LL * (n - 11) * 49);
    return 0;
}