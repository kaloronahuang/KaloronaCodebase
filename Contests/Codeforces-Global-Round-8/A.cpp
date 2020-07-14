// A.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T, a, b, n;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &a, &b, &n);
        int ans = 0;
        while (max(a, b) <= n)
        {
            if (a > b)
                swap(a, b);
            a += b, ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}