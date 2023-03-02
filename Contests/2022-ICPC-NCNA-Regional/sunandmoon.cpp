// E.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int t = 0; t <= 5000; t++)
        if ((a + t) % b == 0 && (c + t) % d == 0)
            printf("%d\n", t), exit(0);
    return 0;
}