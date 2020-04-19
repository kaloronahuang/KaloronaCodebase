// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, nxt[MAX_N];
char str[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), nxt[i] = i - val;
    str[1] = 'a';
    for (int i = 2; i <= n; i++)
    {
        if (nxt[i])
            str[i] = str[nxt[i]];
        else
        {
            int pos = nxt[i - 1] + 1, stat = 1;
            while (pos != 1)
                stat |= (1 << (str[pos] - 'a')), pos = nxt[pos - 1] + 1;
            for (int j = 0; j < 26; j++)
                if ((stat & (1 << j)) == 0)
                {
                    str[i] = 'a' + j;
                    break;
                }
        }
    }
    printf("%s\n", str + 1);
    return 0;
}