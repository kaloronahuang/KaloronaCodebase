// CF1098D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 33;

int q, sum[MAX_N];
multiset<int> blocks[MAX_N];
char cmdlet[MAX_N];

int main()
{
    scanf("%d", &q);
    int cnt = 0, x;
    while (q--)
    {
        scanf("%s%d", cmdlet + 1, &x);
        int block_tot = 31 - __builtin_clz(x);
        if (cmdlet[1] == '+')
            blocks[block_tot].insert(x), sum[block_tot] += x, cnt++;
        else
            blocks[block_tot].erase(blocks[block_tot].find(x)), sum[block_tot] -= x, cnt--;
        int ans = max(0, cnt - 1), cur = sum[0];
        for (int i = 1; i < MAX_N; i++)
        {
            if (cur > 0 && !blocks[i].empty() && *blocks[i].begin() > 2LL * cur)
                ans--;
            cur += sum[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}