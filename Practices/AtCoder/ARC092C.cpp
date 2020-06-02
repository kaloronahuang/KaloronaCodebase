// ARC092C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010;

typedef long long ll;

int n, ai[MAX_N];
ll sum[2];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), sum[i & 1] += max(0, ai[i]);
    if (max(sum[0], sum[1]) == 0)
    {
        int pos = max_element(ai + 1, ai + 1 + n) - ai;
        printf("%d\n%d\n", ai[pos], n - 1);
        for (int i = n; i > pos; i--)
            printf("%d\n", i);
        for (int i = pos - 1; i >= 1; i--)
            puts("1");
        return 0;
    }
    int parity = sum[1] >= sum[0];
    vector<int> pos, ans;
    for (int i = 1; i <= n; i++)
        if (ai[i] > 0 && i % 2 == parity)
            pos.push_back(i);
    for (int i = n; i > pos.back(); i--)
        ans.push_back(i);
    for (int i = 1; i < pos.front(); i++)
        ans.push_back(1);
    for (int i = 0, siz = pos.size(); i < siz - 1; i++)
    {
        for (int j = 0; j < ((pos[i + 1] - pos[i] - 1) >> 1); j++)
            ans.push_back(3);
        ans.push_back(2);
    }
    printf("%lld\n%lld\n", sum[parity], 1LL * ans.size());
    for (int v : ans)
        printf("%d\n", v);
    return 0;
}