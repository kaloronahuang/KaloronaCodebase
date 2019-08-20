// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10010, MAX_Q = 110;

int n, len, q, ans[MAX_Q][MAX_N], seq[MAX_N], queries[MAX_N];
int pos[MAX_N], vis[MAX_N];

void preprocess()
{
    for (int length = 1; length <= n - len; length++)
    {
        int cur1 = 1, cur2 = 1 + length, result = 0;
        for (int i = 0; i < len; i++)
            if (seq[cur1 + i] != seq[cur2 + i])
                result++;
        ans[pos[result]][cur1]++, ans[pos[result]][cur2]++;
        while (cur2 + len <= n)
        {
            result -= (seq[cur1] != seq[cur2]);
            result += (seq[cur1 + len] != seq[cur2 + len]);
            cur1++, cur2++;
            ans[pos[result]][cur1]++, ans[pos[result]][cur2]++;
        }
    }
}

int main()
{
	freopen("lottery.in", "r", stdin);
	freopen("lottery.out", "w", stdout);
    scanf("%d%d", &n, &len);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    scanf("%d", &q), pos[1] = 1;
    for (int i = 1; i <= q; i++)
        scanf("%d", &queries[i]), vis[queries[i]] = 1;
    for (int i = 2; i <= len; i++)
        pos[i] = pos[i - 1] + vis[i - 1];
    preprocess();
    for (int i = 1; i + len - 1 <= n; i++)
        for (int j = 1; j <= q; j++)
            ans[j][i] += ans[j - 1][i];
    for (int i = 1; i <= q; i++, puts(""))
        for (int j = 1; j + len - 1 <= n; j++)
            printf("%d ", ans[pos[queries[i]]][j]);
    return 0;
}

