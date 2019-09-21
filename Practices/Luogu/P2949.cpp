// P2949.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

struct task
{
    int di, pi;
    bool operator<(const task &tsk) const { return pi > tsk.pi; }
} tasks[MAX_N];
priority_queue<task> pq;

int n;

bool compare(task a, task b) { return a.di < b.di; }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &tasks[i].di, &tasks[i].pi);
    sort(tasks + 1, tasks + 1 + n, compare);
    long long ans = 0, siz = 0;
    for (int i = 1; i <= n; i++)
    {
        if (tasks[i].di <= siz)
        {
            if (!pq.empty() && pq.top().pi < tasks[i].pi)
                ans -= pq.top().pi, pq.pop(), pq.push(tasks[i]), ans += tasks[i].pi;
        }
        else
            pq.push(tasks[i]), ans += tasks[i].pi, siz++;
    }
    printf("%lld", ans);
    return 0;
}