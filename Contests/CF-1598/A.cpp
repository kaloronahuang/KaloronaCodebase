// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int T, n;
char mp[3][MAX_N];

int decode(int x)
{
    return (('1' - mp[2][x]) << 1) + ('1' - mp[1][x]);
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s%s", &n, mp[1] + 1, mp[2] + 1);
        bool flag = true;
        for (int i = 2; i <= n; i++)
            flag &= (decode(i) != 0);
        if (flag)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}