// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 200;

int T, n, patt[MAX_N][10];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= 5; j++)
                scanf("%d", &patt[i][j]);
        bool flag = false;
        for (int a = 1; a <= 5; a++)
            for (int b = a + 1; b <= 5; b++)
            {
                int ap = 0, bp = 0, abp = 0;
                for (int i = 1; i <= n; i++)
                    if (patt[i][a] && patt[i][b])
                        abp++;
                    else if (patt[i][a])
                        ap++;
                    else if (patt[i][b])
                        bp++;
                if (ap <= (n >> 1) && bp <= (n >> 1) && ap + bp + abp == n)
                {
                    flag = true;
                    break;
                }
            }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}