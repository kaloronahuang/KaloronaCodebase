// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1100;

int n, m, rev[MAX_N];
char str[MAX_N][MAX_N], tmp[MAX_N];
bool vis[MAX_N];
vector<int> self_palin;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", str[i] + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        memcpy(tmp, str[i], sizeof(tmp)), reverse(tmp + 1, tmp + 1 + m);
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                bool flag = true;
                for (int k = 1; k <= m; k++)
                    if (tmp[k] != str[j][k])
                    {
                        flag = false;
                        break;
                    }
                if (flag)
                    rev[i] = j, cnt++;
            }
        if (strcmp(tmp + 1, str[i] + 1) == 0)
            self_palin.push_back(i);
    }
    printf("%d\n", m * (cnt + (!self_palin.empty())));
    stack<int> ret_stk;
    for (int i = 1; i <= n; i++)
        if (!vis[i] && rev[i] != 0)
            printf("%s", str[i] + 1), ret_stk.push(rev[i]), vis[rev[i]] = true;
    if (!self_palin.empty())
        printf("%s", str[self_palin[0]] + 1);
    while (!ret_stk.empty())
        printf("%s", str[ret_stk.top()] + 1), ret_stk.pop();
    return 0;
}