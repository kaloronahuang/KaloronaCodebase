// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 2000;

int q, n, m, cnt_row[MAX_N], cnt_col[MAX_N];

string opt[MAX_N];

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        memset(cnt_row, 0, sizeof(cnt_row)), memset(cnt_col, 0, sizeof(cnt_col));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
        {
            cin >> opt[i];
            for (int j = 0; j < m; j++)
                if (opt[i][j] == '*')
                    cnt_row[i]++, cnt_col[j + 1]++;
        }
        int ans = n + m - 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                ans = min(ans, n + m - 1 - cnt_row[i] - cnt_col[j] + (opt[i][j - 1] == '*' ? 1 : 0));
        printf("%d\n", ans);
    }
    return 0;
}