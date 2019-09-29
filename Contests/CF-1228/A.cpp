// A.cpp
#include <bits/stdc++.h>

using namespace std;

bool vis[10];

int main()
{
    int l, r;
    scanf("%d%d", &l, &r);
    for (int i = l; i <= r; i++)
    {
        memset(vis, 0, sizeof(vis));
        int tmp = i;
        bool flag = false;
        while (tmp)
        {
            if (vis[tmp % 10] == true)
            {
                flag = true;
                break;
            }
            vis[tmp % 10] = true, tmp /= 10;
        }
        if (!flag)
            printf("%d", i), exit(0);
    }
    puts("-1");
    return 0;
}