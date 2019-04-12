// C_ext.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5050;
int n, q, li[MAX_N], ri[MAX_N], seg_1[MAX_N], seg_2[MAX_N], num[MAX_N], tot;
int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d", &li[i], &ri[i]);
        for (int pt = li[i]; pt <= ri[i]; pt++)
            tot += (num[pt] == 0) ? 1 : 0, num[pt]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if (num[i] == 1)
            seg_1[i] = 1;
        if (num[i] == 2)
            seg_2[i] = 1;
        seg_1[i] += seg_1[i - 1], seg_2[i] += seg_2[i - 1];
    }
    int ans = 0;
    for (int i = 1; i <= q; i++)
        for (int j = 1; j < i; j++)
        {
            int a = i, b = j;
            if (li[a] > li[b])
                swap(a, b);
            int pubL = li[b], pubR = min(ri[b], ri[a]);
            if (pubL > pubR)
                ans = max(ans, tot - (seg_1[ri[i]] - seg_1[li[i] - 1]) - (seg_1[ri[j]] - seg_1[li[j] - 1]));
            else
                ans = max(ans, tot - (seg_1[ri[i]] - seg_1[li[i] - 1]) - (seg_1[ri[j]] - seg_1[li[j] - 1]) - (seg_2[pubR] - seg_2[pubL - 1]));
        }
    printf("%d", ans);
    return 0;
}