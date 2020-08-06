// courses.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_M = 5e4 + 200, MAX_P = 20;

int m, T, ni[MAX_M], si[MAX_M], p, nsum, npre[MAX_M];

struct node
{
    int weight, cost, id;
    bool operator<(const node &rhs) const { return cost < rhs.cost; }
};
vector<node> nodes[MAX_M];

struct requirement
{
    int opt, a1, b1, a2, b2, c;
} reqs[MAX_P];

namespace Subtask1
{

    int mreq[MAX_M];

    int getId(int x, int y) { return npre[x - 1] + y; }

    int handler()
    {
        for (int i = 1; i <= m; i++)
            npre[i] = npre[i - 1] + ni[i];
        long long gans = 1e18;
        for (int stat = 0; stat < (1 << nsum); stat++)
        {
            int tot_pts = 0;
            long long tot_cost = 0;
            for (int i = 1; i <= m; i++)
                mreq[i] = 0;
            for (int i = 1; i <= m; i++)
                for (int j = 1; j <= ni[i]; j++)
                {
                    int u = getId(i, j);
                    if (stat & (1 << (u - 1)))
                    {
                        mreq[i] += nodes[i][j - 1].weight, tot_pts += nodes[i][j - 1].weight;
                        tot_cost += nodes[i][j - 1].cost;
                    }
                }
            bool valid = true;
            for (int i = 1; i <= m; i++)
                valid &= mreq[i] >= si[i];
            for (int i = 1; i <= p; i++)
                if (reqs[i].opt == 1 && ((stat & (1 << (getId(reqs[i].a1, reqs[i].a2) - 1))) && (stat & (1 << (getId(reqs[i].b1, reqs[i].b2) - 1)))))
                    tot_cost -= reqs[i].c;
                else if (reqs[i].opt == 2 && ((stat & (1 << (getId(reqs[i].a1, reqs[i].a2) - 1))) && (stat & (1 << (getId(reqs[i].b1, reqs[i].b2) - 1)))))
                    tot_cost += reqs[i].c;
                else if (reqs[i].opt == 3 && ((stat & (1 << (getId(reqs[i].a1, reqs[i].a2) - 1))) && (stat & (1 << (getId(reqs[i].b1, reqs[i].b2) - 1)))))
                    valid = false;
            if (tot_pts >= T && valid)
                gans = min(gans, tot_cost);
        }
        if (gans == 1e18)
            puts("-1");
        else
            printf("%lld\n", gans);
        return 0;
    }

} // namespace Subtask1

namespace Subtask3
{
    int handler()
    {
        for (int i = 1; i <= m; i++)
            sort(nodes[i].begin(), nodes[i].end());
        vector<int> rem;
        long long ans = 0;
        for (int i = 1; i <= m; i++)
            for (int j = 0, siz = nodes[i].size(); j < siz; j++)
                if (j + 1 <= si[i])
                    ans += nodes[i][j].cost, T--;
                else
                    rem.push_back(nodes[i][j].cost);
        sort(rem.begin(), rem.end());
        for (int i = 0, siz = rem.size(); i < siz && T > 0; i++)
            ans += rem[i], T--;
        if (T > 0)
            puts("-1");
        else
            printf("%lld\n", ans);
    }
} // namespace Subtask3

int main()
{
    freopen("courses.in", "r", stdin);
    freopen("courses.out", "w", stdout);
    bool wi1 = true;
    scanf("%d%d", &m, &T);
    for (int ptr = 1; ptr <= m; ptr++)
    {
        scanf("%d%d", &ni[ptr], &si[ptr]), nsum += ni[ptr];
        node curt;
        for (int i = 1; i <= ni[ptr]; i++)
            scanf("%d%d", &curt.weight, &curt.cost), curt.id = i, nodes[ptr].push_back(curt), wi1 &= curt.weight == 1;
    }
    scanf("%d", &p);
    for (int i = 1; i <= p; i++)
    {
        scanf("%d%d%d%d%d", &reqs[i].opt, &reqs[i].a1, &reqs[i].a2, &reqs[i].b1, &reqs[i].b2);
        if (reqs[i].opt <= 2)
            scanf("%d", &reqs[i].c);
    }
    if (nsum <= 15)
        return Subtask1::handler();
    else if (p == 0 && wi1)
        return Subtask3::handler();
    return 0;
}