// P4835.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int typA, typB, n, seqA[MAX_N], seqB[MAX_N], timA[MAX_N], timB[MAX_N], mxA, mxB;
pair<int, int> dots[MAX_N];

bool check(int mid)
{
    priority_queue<int> local;
    while (!local.empty())
        local.pop();
    int curA = 0;
    for (int i = 1; i <= typA; i++)
    {
        while (curA + 1 <= n && dots[curA + 1].first < seqA[i])
            local.push(dots[++curA].second);
        int k = mid;
        while (k-- && !local.empty())
            local.pop();
    }
    while (curA + 1 <= n)
        local.push(dots[++curA].second);
    int cursor = typB, tim = 0;
    while (!local.empty())
    {
        if (tim == mid)
            cursor--, tim = 0;
        if (cursor < 1)
            return false;
        if (local.top() >= seqB[cursor])
            return false;
        local.pop(), tim++;
    }
    return true;
}

int main()
{
    scanf("%d%d%d", &typA, &typB, &n);
    for (int i = 1; i <= typA; i++)
        scanf("%d", &seqA[i]), mxA = max(mxA, seqA[i]);
    for (int i = 1; i <= typB; i++)
        scanf("%d", &seqB[i]), mxB = max(mxB, seqB[i]);
    sort(seqA + 1, seqA + 1 + typA), sort(seqB + 1, seqB + 1 + typB);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &dots[i].first, &dots[i].second);
        if (dots[i].first >= mxA && dots[i].second >= mxB)
            puts("Impossible"), exit(0);
    }
    sort(dots + 1, dots + 1 + n);
    int l = 1, r = n, ans = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    printf("%d", ans);
    return 0;
}