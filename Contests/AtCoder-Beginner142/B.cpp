// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, k;

int main()
{
    scanf("%d%d", &n, &k);
    int ans = 0, tmp;
    while (n--)
        scanf("%d", &tmp), ans += (tmp >= k);
    printf("%d", ans);
    return 0;
}