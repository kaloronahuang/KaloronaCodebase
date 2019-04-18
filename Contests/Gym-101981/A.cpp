// A.cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int main()
{
    scanf("%d%d", &n, &k);
    if (n == 0)
        printf("Austin"), exit(0);
    if (k != 1 && n != 0)
        printf("Adrien"), exit(0);
    if (k == 1)
        printf((n & 1) ? "Adrien" : "Austin"), exit(0);
    return 0;
}