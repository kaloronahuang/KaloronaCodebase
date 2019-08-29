// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 20;

int n, seq[MAX_N];

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);

    // O(n ^ 2)
    int gans = 0x3f3f3f3f;
    for (int i = 0; i < n; i++)
    {
        int ans = 0;
        for (int j = 1; j <= n; j++)
            ans += abs(seq[j] - ((j - i + n - 1) % n + 1));
        gans = min(gans, ans);
    }
    printf("%d", gans);
    return 0;
}

