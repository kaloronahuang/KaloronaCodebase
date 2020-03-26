// P3566.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int kind, start_pt, end_pt, n, ans[MAX_N];

struct node
{
    int color, cnt;
    bool operator<(const node &rhs) const { return cnt < rhs.cnt || (cnt == rhs.cnt && color != end_pt); }
};

priority_queue<node> pq;

int main()
{
    scanf("%d%d%d", &kind, &start_pt, &end_pt);
    for (int i = 1, val; i <= kind; i++)
    {
        scanf("%d", &val), n += val;
        val -= (i == start_pt) + (i == end_pt);
        if (val < 0)
            printf("0"), exit(0);
        if (val > 0)
            pq.push(node{i, val});
    }
    ans[1] = start_pt, ans[n] = end_pt;
    for (int i = 2; i < n; i++)
    {
        node curt = pq.top();
        pq.pop();
        if (curt.color == ans[i - 1])
            if (!pq.empty())
            {
                node tmp = pq.top();
                pq.pop();
                ans[i] = tmp.color, tmp.cnt--;
                if (tmp.cnt > 0)
                    pq.push(tmp);
                pq.push(curt);
            }
            else
                printf("0"), exit(0);
        else
        {
            node tmp = curt;
            ans[i] = tmp.color, tmp.cnt--;
            if (tmp.cnt > 0)
                pq.push(tmp);
        }
    }
    if (ans[n - 1] == ans[n])
        printf("0"), exit(0);
    for (int i = 1; i <= n; i++)
    {
        printf("%d", ans[i]);
        if (i != n)
            putchar(' ');
    }
    return 0;
}