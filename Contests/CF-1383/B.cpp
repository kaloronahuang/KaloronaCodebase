// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, ai[MAX_N], bucket[30];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(bucket, 0, sizeof(bucket)), scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]);
        if (n == 1)
            puts((ai[1] == 0) ? "DRAW" : "WIN");
        else if (n == 2)
            puts((ai[1] == ai[2]) ? "DRAW" : "WIN");
        else
        {
            for (int i = 1; i <= n; i++)
                for (int b = 0; b < 30; b++)
                    bucket[b] += ((ai[i] >> b) & 1);
            int winningPoint = -1;
            for (int b = 0; b < 30; b++)
                if (bucket[b] & 1)
                    winningPoint = b;
            if (winningPoint == -1)
                puts("DRAW");
            else
                puts((((bucket[winningPoint] - 1) >> 1) & 1) ? "LOSE" : "WIN");
        }
    }
    return 0;
}