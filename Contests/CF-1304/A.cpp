// A.cpp
#include <bits/stdc++.h>

using namespace std;

int T, x, y, a, b;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d%d", &x, &y, &a, &b);
        int delta = y - x;
        if (delta % (a + b) == 0)
            printf("%d\n", delta / (a + b));
        else
            printf("-1\n");
    }
    return 0;
}