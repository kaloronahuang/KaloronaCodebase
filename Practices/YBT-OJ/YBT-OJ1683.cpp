// YBT-OJ1683.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 660;

int n, m, len[MAX_N], ans;
int mapper[MAX_N][MAX_N];
bool c_mapper[MAX_N];
char opt[MAX_N][MAX_N];
ll stat[MAX_N];

void dfs(int pos, int cnt, ll stat_all)
{
    if (cnt + m - pos + 1 < ans)
        return;
    if (pos == m + 1)
    {
        ans = max(ans, cnt);
        return;
    }
    if (!((stat_all >> (pos - 1)) & 1))
        dfs(pos + 1, cnt + 1, stat_all | stat[pos]);
    dfs(pos + 1, cnt, stat_all);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", opt[i] + 1);
        len[i] = strlen(opt[i] + 1);
        for (int j = 1, ele; j <= len[i]; j++)
            scanf("%d", &ele), mapper[i][opt[i][j]] = ele;
    }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            if (i != j)
            {
                bool flag = false;
                for (char c = 'A'; c <= 'Z'; c++)
                    if (mapper[i][c] && mapper[j][c] && mapper[i][c] != mapper[j][c])
                    {
                        flag = true;
                        break;
                    }
                memset(c_mapper, 0, sizeof(c_mapper));
                for (char c = 'A', x; c <= 'Z'; c++)
                    if (mapper[i][c] || mapper[j][c])
                    {
                        if (mapper[i][c] == 0)
                            x = mapper[j][c];
                        else
                            x = mapper[i][c];
                        if (c_mapper[x] == false)
                            c_mapper[x] = true;
                        else
                        {
                            flag = true;
                            break;
                        }
                    }
                if (flag)
                    stat[i] |= (1LL << (j - 1));
            }
    dfs(1, 0, 0), printf("%d\n", ans);
    return 0;
}