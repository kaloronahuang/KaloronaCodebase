// J.cpp
#include <bits/stdc++.h>

using namespace std;

int seq[100100], n;

int main()
{
    while (~scanf("%d", &n))
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]);
        for (int i = 1; i <= n - 1; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            sum += min(seq[x], seq[y]);
        }
        printf("%d\n", sum);
    }

    return 0;
}