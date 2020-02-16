// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int T, n, ans1[MAX_N];
char str[MAX_N];

bool vis_in[MAX_N], vis_out[MAX_N];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s", &n, str + 1);
        for (int rd = 0; rd <= 1; rd++)
        {
            memset(vis_in, 0, sizeof(vis_in)), memset(vis_out, 0, sizeof(vis_out));
            for (int i = 1, last_ptr = -1; i <= n; i++)
            {
                if (str[i] == '<' && last_ptr == -1)
                    last_ptr = i;
                else if ((str[i] == '>' || i == n) && last_ptr != -1)
                    vis_in[last_ptr] = true, vis_out[i] = true, last_ptr = -1;
            }
            stack<int> ans, tmp;
            for (int i = n, flag = 0; i >= 1; i--)
            {
                if (vis_in[i])
                {
                    ans.push(i);
                    while (!tmp.empty())
                        ans.push(tmp.top()), tmp.pop();
                    flag = 0;
                }
                else if (vis_out[i])
                    flag = 1, tmp.push(i);
                else if (flag)
                    tmp.push(i);
                else
                    ans.push(i);
            }
            for (int i = n; i >= 1; i--)
                ans1[ans.top()] = i, ans.pop();
            if (rd == 1)
                reverse(ans1 + 1, ans1 + 1 + n);
            for (int i = 1; i <= n; i++)
                printf("%d ", ans1[i]);
            puts("");
            reverse(str + 1, str + n);
            for (int i = 1; i <= n - 1; i++)
                if (str[i] == '>')
                    str[i] = '<';
                else
                    str[i] = '>';
            // printf("%s\n", str + 1);
        }
    }
    return 0;
}