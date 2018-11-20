// P2859.cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
using namespace std;
const int maxn = 50200;
struct cow
{
    int idx, st, ed;
    bool operator<(const cow &cw) const
    {
        return st < cw.st;
    }
} cows[maxn];
struct node
{
    int idx, edtime;
    bool operator<(const node &nd) const
    {
        return edtime > nd.edtime;
    }
};
priority_queue<node> nodes;
int lines[maxn], ans[maxn], N, m;

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d%d", &cows[i].st, &cows[i].ed), cows[i].idx = i;
    sort(cows + 1, cows + 1 + N);
    for (int i = 1; i <= N; i++)
    {
        if (nodes.empty())
        {
            m++;
            ans[cows[i].idx] = m;
            nodes.push(node{m, cows[i].ed});
        }
        else
        {
            node topp = nodes.top();
            if (topp.edtime < cows[i].st)
            {
                ans[cows[i].idx] = topp.idx;
                nodes.pop();
                topp.edtime = cows[i].ed;
                nodes.push(topp);
            }
            else
            {
                m++;
                ans[cows[i].idx] = m;
                nodes.push(node{m, cows[i].ed});
            }
        }
    }
    printf("%d\n", m);
    for (int i = 1; i <= N; i++)
        printf("%d\n", ans[i]);
    return 0;
}