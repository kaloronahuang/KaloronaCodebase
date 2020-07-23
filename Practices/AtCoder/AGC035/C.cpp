// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n;

int main()
{
    scanf("%d", &n);
    if (__builtin_popcount(n) == 1)
        puts("No"), exit(0);
    puts("Yes"), printf("1 2\n2 3\n3 %d\n%d %d\n%d %d\n", n + 1, n + 1, n + 2, n + 2, n + 3);
    for (int i = 4; i < n; i += 2)
        printf("1 %d\n%d %d\n1 %d\n%d %d\n", i, i, i + 1 + n, i + 1, i + 1, i + n);
    if (!(n & 1))
    {
        for (int i = 2; i <= n; i++)
        {
            int u = i ^ n ^ 1;
            if (i != 3 && u != 3 && u <= n)
            {
                printf("%d %d\n%d %d\n", i, n, u, 2 * n);
                break;
            }
        }
    }
    return 0;
}