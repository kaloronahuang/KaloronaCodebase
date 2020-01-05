// A.cpp
#include <bits/stdc++.h>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + (ch - '0'), ch = getchar();
    return x * f;
}

const int MAX_N = 1e5 + 200;

int T, n;
char str[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s", &n, str + 1);
        int first_pos = 0;
        for (; first_pos <= n; first_pos++)
            if (str[first_pos] == 'A')
                break;
        int last = -1, ans = 0;
        for (int i = first_pos; i <= n + 1; i++)
            if (str[i] == 'P' && last == -1)
                last = i;
            else if (str[i] != 'P' && last != -1)
                ans = max(ans, i - last), last = -1;
        printf("%d\n", ans);
    }
    return 0;
}