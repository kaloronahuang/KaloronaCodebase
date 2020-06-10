// P4574.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 33;

int a, b, c;

int main()
{
    scanf("%d%d%d", &a, &b, &c);
    int tA = __builtin_popcount(a), tB = __builtin_popcount(b), tC = __builtin_popcount(c);
    int n = max({log2(a) + 1, log2(b) + 1, log2(c) + 1});
    if (tA > tB)
        swap(tA, tB);
    int ans = 0;
    if (tC <= tA)
        ans = (1 << (tA + tB - tC)) | ((1 << tC) - 2);
    else if (tC <= tB)
        ans = ((1 << tB) | ((1 << tC) - 1)) ^ (1 << (tC - tA));
    else if (tC <= tA + tB)
        ans = ((1 << (tC + 1)) - 1) ^ (1 << (tC + tC - tA - tB));
    else
        ans = -1;
    if (int(log2(ans) + 1) > n)
        ans = -1;
    printf("%d\n", ans);
    return 0;
}