// A.cpp
#include <bits/stdc++.h>
 
using namespace std;
 
const int MAX_N = 105;
 
int T, n;
char str[MAX_N];
 
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s", &n, str + 1);
        if (n == 1)
        {
            puts("-1 -1");
            continue;
        }
        bool found = false;
        for (int i = 1; i < n && !found; i++)
            if ((str[i] ^ str[i + 1]) != 0)
                printf("%d %d\n", i, i + 1), found = true;
        if (!found)
            puts("-1 -1");
    }
    return 0;
}