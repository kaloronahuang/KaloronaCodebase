// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, k, mi[MAX_N], ci[MAX_N], ptot;
deque<int> packs[MAX_N];

struct cmp
{
    bool operator()(const int &a, const int &b) const { return packs[a].size() > packs[b].size(); }
};

priority_queue<int, vector<int>, cmp> pq;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &mi[i]);
    for (int i = 1; i <= k; i++)
        scanf("%d", &ci[i]);
    sort(mi + 1, mi + 1 + n);
    int ptr = n;
    for (int i = k; i >= 1; i--)
    {
        deque<int> tmp;
        while (ptr >= 1 && mi[ptr] >= i)
            tmp.push_back(mi[ptr]), ptr--;
        while (!tmp.empty())
        {
            if (pq.empty() || packs[pq.top()].size() >= ci[i])
                pq.push(++ptot);
            int u = pq.top();
            pq.pop();
            while (packs[u].size() < ci[i] && !tmp.empty())
                packs[u].push_back(tmp.front()), tmp.pop_front();
            pq.push(u);
        }
    }
    printf("%d\n", ptot);
    for (int i = 1; i <= ptot; i++)
    {
        printf("%lld ", 1LL * packs[i].size());
        for (auto x : packs[i])
            printf("%d ", x);
        puts("");
    }
    return 0;
}