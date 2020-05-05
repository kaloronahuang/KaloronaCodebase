// CF1348C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, k;
char str[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%s", &n, &k, str + 1);
        sort(str + 1, str + 1 + n);
        if (str[1] != str[k])
            printf("%c\n", str[k]);
        else
        {
            putchar(str[1]);
            if (str[k + 1] != str[n])
                printf("%s", str + k + 1);
            else
                for (int i = 1; i <= (n - k + k - 1) / k; i++)
                    printf("%c", str[n]);
            puts("");
        }
    }
    return 0;
}