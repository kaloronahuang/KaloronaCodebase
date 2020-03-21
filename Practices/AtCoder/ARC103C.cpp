// ARC103C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, fa[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    if (str[1] == '0' || str[n] == '1')
        puts("-1"), exit(0);
    for (int i = 1, j = n - 1; i <= j; i++, j--)
        if (str[i] != str[j])
            puts("-1"), exit(0);
    int root = 1;
    for (int i = 2; i <= n; i++)
    {
        printf("%d %d\n", root, i);
        if (str[i - 1] == '1')
            root = i;
    }
    return 0;
}