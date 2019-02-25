// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
int n, seqA[MAX_N], seqB[MAX_N], tmp[MAX_N], ca[MAX_N], cb[MAX_N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        seqA[a]++, seqB[b]++;
        memcpy(ca, seqA, sizeof(seqA)), memcpy(cb, seqB, sizeof(seqB));
        int cur1 = 100, cur2 = 1;
        int ans = 0;
        while (cur1 < 101 && cur2 > 0)
        {
            while (ca[cur1] == 0 && cur1 > 0)
                cur1--;
            while (cb[cur2] == 0 && cur2 < 101)
                cur2++;
            if (cur1 == 0 || cur2 == 101)
                break;
            ans = max(ans, cur1 + cur2);
            if (ca[cur1] > cb[cur2])
                ca[cur1] -= cb[cur2], cb[cur2] = 0;
            else
                cb[cur2] -= ca[cur1], ca[cur1] = 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}