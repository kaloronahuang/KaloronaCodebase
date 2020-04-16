// B.cpp
#include <bits/stdc++.h>

using namespace std;

int T, x, n, m;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &x, &n, &m);
        int bas = x;
        bool flag = false;
        for (int i = 0; i <= n; i++)
        {
            if (bas - m * 10 <= 0)
            {
                flag = true;
                break;
            }
            bas = (bas >> 1) + 10;
        }
        if (flag)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}