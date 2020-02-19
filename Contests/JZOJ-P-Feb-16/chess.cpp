// chess.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, k, ans;

struct node
{
    int x, y;

    bool operator<(const node &rhs) const { return x < rhs.x || (x == rhs.x && y < rhs.y); }
} nodes[MAX_N];

map<node, bool> mp;

void fileIO()
{
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
}

int main()
{
    // fileIO();
    scanf("%d%d", &n, &k);
    if (n <= k)
        puts("-1"), exit(0);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &nodes[i].x, &nodes[i].y);
    sort(nodes + 1, nodes + 1 + n);
    if (k == 0)
    {
        // matching;
        int xmin = 0x7fffffff, xmax = -0x7fffffff, ymin = 0x7fffffff, ymax = -0x7fffffff;
        for (int i = 1; i <= n; i++)
        {
            xmin = min(xmin, nodes[i].x), xmax = max(xmax, nodes[i].x);
            ymin = min(ymin, nodes[i].y), ymax = max(ymax, nodes[i].y);
        }
        for (int i = 1; i < (n - i + 1); i++)
            if ((nodes[i].x + nodes[n - i + 1].x != xmax + xmin) || (nodes[i].y + nodes[n - i + 1].y != ymax + ymin))
                puts("0"), exit(0);
        puts("1"), exit(0);
    }
    else
    {
        int ans = 0;
        for (int i = 1; i <= k + 1; i++)
            for (int j = n - k; j <= n; j++)
            {
                int xsum = nodes[i].x + nodes[j].x, ysum = nodes[i].y + nodes[j].y;
                if (!mp.count(node{xsum, ysum}))
                {
                    mp[node{xsum, ysum}] = true;
                    int lptr = 1, rptr = n, matching = 0;
                    while (lptr <= n && rptr >= 1)
                    {
                        if (nodes[lptr].x + nodes[rptr].x == xsum && nodes[lptr].y + nodes[rptr].y == ysum)
                            matching++, lptr++, rptr--;
                        else if (nodes[lptr] < node{xsum - nodes[rptr].x, ysum - nodes[rptr].y})
                            lptr++;
                        else
                            rptr--;
                        if (n - matching - min(n - lptr + 1, rptr) > k)
                            break;
                    }
                    if (n - matching <= k)
                        ans++;
                }
            }
        printf("%d\n", ans);
    }
    return 0;
}