// P1860.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, INF = 0x3f3f3f3f;

int n, m, v, k, inprice[MAX_N], outprice[MAX_N], gen[MAX_N][MAX_N];
int tmp[110][110], dp[MAX_N][1010];

struct composition
{
    int prod, siz;
    vector<int> src;
} coms[330];

int main()
{
    scanf("%d%d%d%d", &n, &m, &v, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &inprice[i], &outprice[i]);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &coms[i].prod, &coms[i].siz);
        for (int j = 1, tmp; j <= coms[i].siz; j++)
            scanf("%d", &tmp), coms[i].src.push_back(tmp);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= k; j++)
            gen[i][j] = INF;
        gen[i][0] = inprice[i];
    }
    for (int gpack = 1; gpack <= k; gpack++)
    {
        for (int i = 1; i <= m; i++)
        {
            // initialize;
            for (int j = 0; j < gpack; j++)
                tmp[0][j] = gen[coms[i].src[0]][j];
            for (int j = 1, siz = coms[i].src.size(); j < siz; j++)
                for (int pack = 0; pack < gpack; pack++)
                {
                    tmp[j][pack] = INF;
                    for (int subpack = 0; subpack <= pack; subpack++)
                        tmp[j][pack] = min(tmp[j][pack], tmp[j - 1][subpack] + gen[coms[i].src[j]][pack - subpack]);
                }
            gen[coms[i].prod][gpack] = min(gen[coms[i].prod][gpack], tmp[coms[i].src.size() - 1][gpack - 1]);
        }
    }
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= v; j++)
            dp[i][j] = -INF;
    dp[0][0] = 0;
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= v; j++)
            for (int id = 1; id <= n; id++)
                for (int gm = 0; gm <= i; gm++)
                    if (gen[id][gm] != INF && j >= gen[id][gm])
                        dp[i][j] = max(dp[i][j], dp[i - gm][j - gen[id][gm]] + outprice[id] - gen[id][gm]);
    int ans = 0;
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= v; j++)
            ans = max(ans, dp[i][j]);
    printf("%d", ans);
    return 0;
}