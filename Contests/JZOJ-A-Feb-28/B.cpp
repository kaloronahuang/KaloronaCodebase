// B.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1010, DOM = 1000;
int ai[MAX_N], bi[MAX_N], n, ans = 0x3f3f3f3f, curt[MAX_N];
bool bucket[MAX_N << 1];
bool check()
{
    for (int i = 1; i <= n; i++)
        if (!bucket[bi[i] + DOM])
            return false;
    return true;
}
bool dfs(int tim)
{
    if (tim == 0 && check())
        return true;
    if (tim == 0)
        return false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                bool flag = true;
                int dst = curt[j] * 2 - curt[i];
                for (int k = 1; k <= n; k++)
                    if (k != j && ((curt[i] <= dst && curt[k] < dst && curt[k] > curt[i]) || (dst <= curt[i] && curt[k] < curt[i] && dst < curt[k])))
                    {
                        flag = false;
                        break;
                    }
                if (flag)
                {
                    int tmp = curt[i], pre = bucket[dst + DOM];
                    curt[i] = dst, bucket[dst + DOM] = true;
                    if (dfs(tim - 1))
                        return true;
                    bucket[dst + DOM] = pre, curt[i] = tmp;
                }
            }
    return false;
}
int main()
{
    n = 3;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), curt[i] = ai[i], bucket[ai[i] + DOM] = true;
    for (int i = 1; i <= n; i++)
        scanf("%d", &bi[i]);
    for (int i = 1; i <= 1000; i++)
        if (dfs(i))
            printf("YES\n%d", i), exit(0);
    printf("NO");
    return 0;
}