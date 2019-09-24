// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

struct node
{
    int id, val;
    bool operator<(const node &nd) const { return val < nd.val; }
    bool operator>(const node &nd) const { return val > nd.val; }
};
priority_queue<node, vector<node>, greater<node>> pqg;
priority_queue<node> pql;
bool vis[MAX_N];
int n, tmp;

int main()
{
    int tot = 0;
    scanf("%d", &n);
    long long ans = 0;
    while (n--)
    {
        int k;
        scanf("%d", &k);
        while (k--)
            scanf("%d", &tmp), pqg.push(node{++tot, tmp}), pql.push(node{tot, tmp});
        while (!pqg.empty() && vis[pqg.top().id])
            pqg.pop();
        while (!pql.empty() && vis[pql.top().id])
            pql.pop();
        ans += pqg.top().val - pql.top().val;
        vis[pqg.top().id] = vis[pql.top().id] = true;
        pqg.pop(), pql.pop();
    }
    printf("%lld", abs(ans));
    return 0;
}