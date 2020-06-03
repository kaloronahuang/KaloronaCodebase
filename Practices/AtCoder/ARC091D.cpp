// ARC091D.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1, x, k; i <= n; i++)
    {
        scanf("%d%d", &x, &k);
        while (x % k != 0)
            x -= ((x % k - 1) / (x / k + 1) + 1) * (x / k + 1);
        ans ^= x / k;
    }
    puts(!ans ? "Aoki" : "Takahashi");
    return 0;
}