// POJ2442.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
int T, m, n, seq[110][2020], seqb[2020], tmp[2020];
struct node
{
    int val, l, r;
    bool flag;
    bool operator<(const node &nd) const
    {
        return val > nd.val;
    }
};

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
                scanf("%d", &seq[i][j]);
            sort(seq[i] + 1, seq[i] + n + 1);
        }
        for (int i = 1; i <= n; i++)
            seqb[i] = seq[1][i];
        for (int ln = 2; ln <= m; ln++)
        {
            priority_queue<node> npool;
            npool.push(node{seqb[1] + seq[ln][1], 1, 1, false});
            int cnt = 1;
            while (cnt <= n)
            {
                node curt = npool.top();
                npool.pop();
                tmp[cnt++] = curt.val;
                if (!curt.flag)
                    npool.push(node{seqb[curt.l + 1] + seq[ln][curt.r], curt.l + 1, curt.r, false});
                npool.push(node{seqb[curt.l] + seq[ln][curt.r + 1], curt.l, curt.r + 1, true});
            }
            for (int i = 1; i <= n; i++)
                seqb[i] = tmp[i];
        }
        for (int i = 1; i <= n; i++)
            printf("%d ", seqb[i]);
        printf("\n");
    }
    return 0;
}