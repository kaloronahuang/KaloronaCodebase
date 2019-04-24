// CH5E02.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 110;
int f, v, contrib[MAX_N][MAX_N], dp[MAX_N][MAX_N], pre[MAX_N][MAX_N];

int main()
{
    scanf("%d%d", &f, &v);
    for (int i = 1; i <= f; i++)
        for (int j = 1; j <= v; j++)
            scanf("%d", &contrib[i][j]);

    memset(dp, ~0x3f, sizeof(dp)), memset(pre, 0x3f, sizeof(pre));
    dp[0][0] = 0;
    for (int i = 1; i <= f; i++)
        for (int j = 1; j <= v; j++)
            for (int k = 0; k < j; k++)
            {
                int curt_ans = dp[i - 1][k] + contrib[i][j];
                if (dp[i][j] < curt_ans)
                    dp[i][j] = curt_ans, pre[i][j] = k;
                if (dp[i][j] == curt_ans && pre[i][j] > k)
                    pre[i][j] = k;
            }
    stack<int> st;
    int j = v, ans = -0x3f3f3f3f;
    for (int pt = v; pt >= f; pt--)
        if (dp[f][pt] >= ans)
            ans = dp[f][pt], j = pt;
    printf("%d\n", ans);
    for (int i = f; i >= 1; i--)
        st.push(j), j = pre[i][j];
    while (!st.empty())
        printf("%d ", st.top()), st.pop();
    return 0;
}