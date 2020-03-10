// CF1067C.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        printf("%d %d\n", (i << 1) / 3, (i << 1) % 3);
    return 0;
}