// CF1086C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int T, n, k;
char S[MAX_N], A[MAX_N], B[MAX_N], temp[30];
bool vis[30];

bool dfs(int pos, bool L, int R)
{
    if (pos == n + 1)
        return true;
    if (temp[S[pos] - 'a'] != 0)
    {
        int target = temp[S[pos] - 'a'];
        if ((!L || target >= A[pos]) && (!R || target <= B[pos]))
            return dfs(pos + 1, L && target == A[pos], R && target == B[pos]);
    }
    else
    {
        for (int i = 0; i < k; i++)
            if (!vis[i] && (!L || i + 'a' >= A[pos]) && (!R || i + 'a' <= B[pos]))
            {
                temp[S[pos] - 'a'] = i + 'a', vis[i] = true;
                if (dfs(pos + 1, L && i + 'a' == A[pos], R && i + 'a' == B[pos]))
                    return true;
                temp[S[pos] - 'a'] = 0, vis[i] = false;
            }
    }
    return false;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%s%s%s", &k, S + 1, A + 1, B + 1), n = strlen(S + 1);
        memset(temp, 0, sizeof(temp)), memset(vis, false, sizeof(vis));
        if (dfs(1, true, true))
        {
            puts("YES");
            for (int i = 0; i < k; i++)
                if (temp[i] == 0)
                {
                    for (int j = 0; j < k; j++)
                        if (!vis[j])
                        {
                            putchar(j + 'a'), vis[j] = true;
                            break;
                        }
                }
                else
                    putchar(temp[i]);
            putchar('\n');
        }
        else
            puts("NO");
    }
    return 0;
}