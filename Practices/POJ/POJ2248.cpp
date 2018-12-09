// POJ2248.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int M, ans[120];
bool vis[120];
bool dfs(int pos, int n)
{
    if (pos == n)
        return ans[pos] == M;
    for (int i = pos; i; i--)
        for (int j = i; j; j--)
        {
            int val = ans[i] + ans[j];
            if (val <= M && val > ans[pos])
            {
                ans[pos + 1] = val;
                if (dfs(pos + 1, n))
                    return true;
            }
        }
    return false;
}

int main()
{
    ans[1] = 1;
    while (scanf("%d", &M) && M)
    {
        int dep = 1;
        while (!dfs(1, dep))
            ++dep;
        for (int i = 1; i <= dep; i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}