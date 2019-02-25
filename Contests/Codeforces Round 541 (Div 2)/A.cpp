// A.cpp
#include <bits/stdc++.h>
using namespace std;
int h1, h2, w1, w2;
int main()
{
    scanf("%d%d%d%d", &w1, &h1, &w2, &h2);
    long long ans = 0;
    // the lower one:
    ans += h1 + 1 + w1 + 1 + h1;
    // the higher one:
    // upper face and left;
    ans += w2 + 2 + h2 + h2;
    ans += abs(w1 - w2);
    printf("%lld", ans);
    return 0;
}