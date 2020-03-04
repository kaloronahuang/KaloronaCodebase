// CF1103A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ux, uy, dx, dy;
char str[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    ux = 1, uy = 1, dx = 0, dy = 1;
    for (int i = 1; i <= n; i++)
        if (str[i] == '0')
            printf("%d %d\n", ux, uy), uy = uy % 4 + 1;
        else
            printf("%d %d\n", (dx >> 1) + 3, dy), dx = (dx + 1) % 4, dy = (dy + 1) % 4 + 1;
    return 0;
}