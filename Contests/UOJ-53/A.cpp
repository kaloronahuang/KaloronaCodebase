// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;
const char st[] = "xl";

int T, n, pre[2][MAX_N];
char str[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", str + 1), n = strlen(str + 1);
        for (int i = 1; i <= n; i++)
        {
            pre[0][i] = pre[1][i] = 0;
            if (str[i] == 'x')
                pre[0][i]++;
            else
                pre[1][i]++;
            pre[0][i] += pre[0][i - 1], pre[1][i] += pre[1][i - 1];
        }
        int ans = 0, lptr = -1, rptr = -1;
        for (int i = 1; i <= n; i++)
            if (pre[0][i] == 3)
            {
                lptr = i;
                break;
            }
        for (int i = n; i >= 1; i--)
            if (pre[1][n] - pre[1][i - 1] == 2)
            {
                rptr = i;
                break;
            }
        if (lptr == -1 || rptr == -1)
            ans = 0;
        else
        {
            ans = max(0, min(pre[1][n] - pre[1][lptr] - 1, pre[0][rptr] - 2));
        }
        printf("%d\n", ans);
    }
    return 0;
}