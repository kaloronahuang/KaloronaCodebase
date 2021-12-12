// candy.cpp
#include <bits/stdc++.h>

using namespace std;

int T, a, b;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &a, &b);
        int ans = (a + b) >> 2;
        ans = min(ans, min(a, b));
        printf("%d\n", ans);
    }
}