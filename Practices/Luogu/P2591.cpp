// P2591.cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    if (m > n / 2)
        m = n - m + 1;
    printf("%d", n == 1 ? 1 : 2 * m);
    return 0;
}