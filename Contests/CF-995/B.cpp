// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

int n, ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= (n << 1); i++)
        scanf("%d", &ai[i]);
    int ans = 0;
    for (int i = 1; i <= (n << 1); i++)
    {
        if (ai[i + 1] == ai[i])
            i++;
        else
        {
            int ptr = 0;
            for (int j = i + 1; j <= (n << 1); j++)
                if (ai[j] == ai[i])
                {
                    ptr = j;
                    break;
                }
            int tmp = ai[ptr];
            for (int j = ptr; j > i + 1; j--)
                ai[j] = ai[j - 1], ans++;
            ai[i + 1] = tmp;
            i++;
        }
    }
    printf("%d\n", ans);
    return 0;
}