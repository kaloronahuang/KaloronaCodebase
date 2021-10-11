// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int T, n;
char str[MAX_N], cmdlet[10], rc;
bool vis[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s%s", &n, cmdlet, str + 1), rc = cmdlet[0];
        bool flag1 = true;
        for (int i = 1; i <= n; i++)
            flag1 &= (str[i] == rc);
        if (flag1)
            puts("0");
        else
        {
            if (str[n] == rc)
                printf("1\n%d\n", n);
            else
            {
                for (int i = 1; i <= n; i++)
                    vis[i] = true;
                for (int i = 1; i <= n; i++)
                    for (int j = i; j <= n; j += i)
                        if (str[j] != rc)
                        {
                            vis[i] = false;
                            break;
                        }
                int pos = -1;
                for (int i = 1; i <= n; i++)
                    if (vis[i])
                        pos = i;
                if (pos != -1)
                    printf("1\n%d\n", pos);
                else
                    printf("2\n%d %d\n", n - 1, n);
            }
        }
    }
    return 0;
}