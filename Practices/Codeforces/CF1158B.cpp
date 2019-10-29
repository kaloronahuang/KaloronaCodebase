// CF1158B.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k, l;
    scanf("%d%d", &n, &k), l = (n - k) / 2;
    for (int i = 1; i <= n; i++)
        printf("%d", (i % (l + 1)) > 0);
    return 0;
}