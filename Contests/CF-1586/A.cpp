// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n, ai[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        int sum = 0;
        for (int i = 1; i <= n; i++)
            scanf("%d", &ai[i]), sum += ai[i];
        bool flag = false;
        for (int i = 2; 1LL * i * i <= sum; i++)
            if (sum % i == 0)
            {
                flag = true;
                break;
            }
        if (flag)
        {
            printf("%d\n", n);
            for (int i = 1; i <= n; i++)
                printf("%d ", i);
        }
        else
        {
            printf("%d\n", n - 1);
            for (int i = 1; i <= n; i++)
            {
                int ssum = sum - ai[i];
                bool flag = false;
                for (int j = 2; 1LL * j * j <= ssum; j++)
                    if (ssum % j == 0)
                    {
                        flag = true;
                        break;
                    }
                if (flag)
                {
                    for (int j = 1; j <= n; j++)
                        if (j != i)
                            printf("%d ", j);
                    break;
                }
            }
        }
        puts("");
    }
    return 0;
}