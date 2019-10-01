// P3661.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200;

struct interval
{
    int l, r;
    bool operator<(const interval &it) const { return r > it.r; }
} its[MAX_N];

int C, N, pos[MAX_N];

bool compare(interval A, interval B) { return A.l < B.l; }

int main()
{
    scanf("%d%d", &C, &N);
    for (int i = 1; i <= C; i++)
        scanf("%d", &pos[i]);
    sort(pos + 1, pos + 1 + C);
    for (int i = 1; i <= N; i++)
        scanf("%d%d", &its[i].l, &its[i].r);
    sort(its + 1, its + 1 + N, compare);
    priority_queue<interval> pq;
    int ans = 0, cur = 1;
    for (int i = 1; i <= C; i++)
    {
        while (cur <= N && its[cur].l <= pos[i])
            pq.push(its[cur++]);
        while (!pq.empty() && pq.top().r < pos[i])
            pq.pop();
        if (!pq.empty())
            ans++, pq.pop();
    }
    printf("%d", ans);
    return 0;
}