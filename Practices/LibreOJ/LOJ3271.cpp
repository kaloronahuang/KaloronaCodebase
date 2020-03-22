// LOJ3271.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, len, ai[MAX_N][2], l[MAX_N][2], r[MAX_N][2];

int main()
{
    scanf("%d", &n), len = n << 1;
    for (int i = 1; i <= len; i++)
        scanf("%d", &ai[i][0]);
    for (int i = 1; i <= len; i++)
        scanf("%d", &ai[i][1]);
    for (int i = 1; i <= len; i++)
    {
        l[i][0] = l[i][1] = len + 1;
        r[i][0] = r[i][1] = -1;
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                if (ai[i][j] >= ai[i - 1][k])
                {
                    l[i][j] = min(l[i][j], l[i - 1][k] + (j == 0));
                    r[i][j] = max(r[i][j], r[i - 1][k] + (j == 0));
                }
    }
    int typ = -1;
    if (l[len][0] <= n && n <= r[len][0])
        typ = 0;
    if (l[len][1] <= n && n <= r[len][1])
        typ = 1;
    if (typ == -1)
        puts("-1"), exit(0);
    stack<char> ansBox;
    for (int i = len, cnt = n; i >= 1; i--)
    {
        ansBox.push(typ ? 'B' : 'A');
        cnt -= (typ == 0);
        for (int j = 0; j <= 1; j++)
            if (ai[i - 1][j] <= ai[i][typ] && l[i - 1][j] <= cnt && cnt <= r[i - 1][j])
            {
                typ = j;
                break;
            }
    }
    while (!ansBox.empty())
        printf("%c", ansBox.top()), ansBox.pop();
    puts("");
    return 0;
}