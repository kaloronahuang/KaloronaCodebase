// 1004.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int main()
{
    int T;
    long long n;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld", &n);
        if (n == 1)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}