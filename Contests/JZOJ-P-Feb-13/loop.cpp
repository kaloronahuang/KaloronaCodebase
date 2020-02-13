// loop.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e6 + 200;

int n, ans[MAX_N];
char str[MAX_N];

int main()
{
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    while (scanf("%s", str + 1) != EOF)
    {
        memset(ans, 0, sizeof(ans));
        n = strlen(str + 1);
        for (int i = 1; i <= n; i++)
            str[i + n] = str[i];
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j - i + 1 <= n; j++)
            {
                int len = j - i + 1;
                if (str[j] == str[j - 1])
                    break;
                if (str[i] != str[j])
                    ans[len] = 1;
            }
        for (int i = n; i >= 1; i--)
            printf("%d", ans[i]);
        puts("");
    }
    return 0;
}