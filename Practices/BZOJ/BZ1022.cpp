// BZ1022.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T, n, a;
    scanf("%d", &T);
    while (T--)
    {
        int sg = 0;
        scanf("%d", &n);
        bool flag = false;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a), sg ^= a;
            if (a > 1)
                flag = true;
        }
        if (sg == 0 && flag == false)
            puts("John");
        else if (sg && flag)
            puts("John");
        else 
            puts("Brother");
    }
    return 0;
}