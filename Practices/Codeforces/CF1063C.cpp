// CF1063C.cpp
#include <bits/stdc++.h>

using namespace std;

int n;
char cmdlet[20];

int query(int x)
{
    printf("%d %d\n", x, 1);
    fflush(stdout);
    scanf("%s", cmdlet + 1);
    return cmdlet[1] == 'b';
}

int main()
{
    scanf("%d", &n);
    int l = 1, r = 1e9, res = 0, last = query(0);
    for (int i = 1; i < n; i++)
    {
        int mid = (l + r) >> 1;
        if (last == query(mid))
            l = mid + 1, res = mid;
        else
            r = mid - 1;
    }
    printf("%d %d %d %d\n", res, 0, res + 1, 2);
    fflush(stdout);
    return 0;
}