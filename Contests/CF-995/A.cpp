// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 202;

int n, k, mat[5][MAX_N], posx[MAX_N], posy[MAX_N];
bool occupy[5][MAX_N];

struct node
{
    int id, x, y;
    bool stat;
};

int main()
{
    scanf("%d%d", &n, &k);
    vector<node> nds;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &mat[i][j]);
            if (i != 1 && i != 4 && mat[i][j] != 0)
                nds.push_back(node{mat[i][j], i, j});
        }
    int cnt = 20000;
    vector<node> rec;
    while (!nds.empty() && (int)rec.size() <= cnt)
    {
        auto it = nds.begin();
        while (it != nds.end())
        {
            auto x = *it;
            if (x.x == 2 && x.id == mat[1][x.y])
            {
                rec.push_back(node{x.id, 1, x.y});
                nds.erase(it);
            }
            else if (x.x == 3 && x.id == mat[4][x.y])
            {
                rec.push_back(node{x.id, 4, x.y});
                nds.erase(it);
            }
            else
                it++;
        }
        vector<node> tmp_rec;
        memset(occupy, false, sizeof(occupy));
        for (auto &x : nds)
            posx[x.id] = x.x, posy[x.id] = x.y, occupy[x.x][x.y] = true;
        for (auto &x : nds)
        {
            auto pre = x;
            if (pre.x == 2)
            {
                pre.y--;
                if (pre.y == 0)
                    pre.y = 1, pre.x = 3;
            }
            else
            {
                pre.y++;
                if (pre.y == n + 1)
                    pre.y = n, pre.x = 2;
            }
            x = pre, tmp_rec.push_back(node{x.id, x.x, x.y});
        }
        while (!tmp_rec.empty())
        {
            bool flag = false;
            it = tmp_rec.begin();
            while (it != tmp_rec.end())
            {
                if (occupy[it->x][it->y] == false)
                {
                    occupy[it->x][it->y] = true;
                    occupy[posx[it->id]][posy[it->id]] = false;
                    rec.push_back(*it);
                    tmp_rec.erase(it), flag = true;
                    break;
                }
                it++;
            }
            if (flag)
                continue;
            else
                puts("-1"), exit(0);
        }
    }
    if (int(rec.size()) <= cnt)
    {
        printf("%lld\n", 1LL * rec.size());
        for (auto x : rec)
            printf("%d %d %d\n", x.id, x.x, x.y);
    }
    else
        puts("-1");
    return 0;
}