// A.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        printf("%d %d %d\n", b, c, min(d, max(c, b + c - 1)));
    }
    return 0;
}