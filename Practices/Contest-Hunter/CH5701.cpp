// CH5701.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;
const int MAX_N = 1e5 + 2000, INF = 0x3f3f3f3f;
multiset<pr> bst;
int n, hi[MAX_N], x0, m, si[MAX_N], xi[MAX_N], ga[MAX_N], gb[MAX_N];
int f[20][MAX_N][2], da[20][MAX_N][2], db[20][MAX_N][2];
int getDist(int i, int j) { return abs(hi[i] - hi[j]); }
pr calc(int s, int x)
{
    int la = 0, lb = 0, pt = s;
    for (int di = 19; di >= 0; di--)
        if (f[di][pt][0] && la + lb + da[di][pt][0] + db[di][pt][0] <= x)
            la += da[di][pt][0], lb += db[di][pt][0], pt = f[di][pt][0];
    return make_pair(la, lb);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &hi[i]);
    scanf("%d%d", &x0, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &si[i], &xi[i]);
    // preprocessing of GA GB passed;
    bst.insert(make_pair(INF, 0)), bst.insert(make_pair(INF, 0));
    bst.insert(make_pair(-INF, 0)), bst.insert(make_pair(-INF, 0));
    for (int i = n; i >= 1; i--)
    {
        bst.insert(make_pair(hi[i], i));
        set<pr>::iterator it = bst.find(make_pair(hi[i], i));
        pr ans;
        if (++it != bst.end())
            ans = make_pair((*it).first - hi[i], (*it).second);
        it = bst.find(make_pair(hi[i], i));
        if ((it--) != bst.begin() &&
            (hi[i] - (*it).first < ans.first ||
             hi[i] - (*it).first == ans.first && hi[(*it).second] < hi[ans.second]))
            ans = make_pair(hi[i] - (*it).first, (*it).second);
        ga[i] = ans.second;
    }
    bst.clear();

    bst.insert(make_pair(INF, 0)), bst.insert(make_pair(INF, 0));
    bst.insert(make_pair(-INF, 0)), bst.insert(make_pair(-INF, 0));
    for (int i = n; i >= 1; i--)
    {
        bst.insert(make_pair(hi[i], i));
        set<pr>::iterator it = bst.find(make_pair(hi[i], i));
        int pval = 0x3f3f3f3f, pkey;
        if (++it != bst.end())
            pval = (*it).first - hi[i], pkey = (*it).second;
        it = bst.find(make_pair(hi[i], i));
        if ((it--) != bst.begin() && (hi[i] - (*it).first > pval || (hi[i] - (*it).first == pval && hi[(*it).second] > hi[pkey])))
            pval = (*it).first - hi[i], pkey = (*it).second;
        gb[i] = pkey;
    }
    bst.clear();
    for (int i = 1; i <= n; i++)
        swap(gb[i], ga[i]);
    // the preprocessing of the destination;
    for (int i = 1; i <= n; i++)
        f[0][i][0] = ga[i], f[0][i][1] = gb[i];
    for (int i = 1; i <= n; i++)
        for (int k = 0; k <= 1; k++)
            f[1][i][k] = f[0][f[0][i][k]][1 - k];
    for (int di = 2; di < 20; di++)
        for (int i = 1; i <= n; i++)
            for (int k = 0; k <= 1; k++)
                f[di][i][k] = f[di - 1][f[di - 1][i][k]][k];
    // the preprocessing of the distances da;
    for (int i = 1; i <= n; i++)
        da[0][i][0] = getDist(ga[i], i), da[0][i][1] = 0;
    for (int i = 1; i <= n; i++)
    {
        da[1][i][0] = da[0][i][0];
        da[1][i][1] = da[0][f[0][i][1]][0];
    }
    for (int di = 2; di < 20; di++)
        for (int i = 1; i <= n; i++)
            for (int k = 0; k <= 1; k++)
                da[di][i][k] = da[di - 1][f[di - 1][i][k]][k] + da[di - 1][i][k];
    // the preprocessing of the distances da;
    for (int i = 1; i <= n; i++)
        db[0][i][1] = getDist(gb[i], i), db[0][i][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        db[1][i][1] = db[0][i][1];
        db[1][i][0] = db[0][f[0][i][0]][1];
    }
    for (int di = 2; di < 20; di++)
        for (int i = 1; i <= n; i++)
            for (int k = 0; k <= 1; k++)
                db[di][i][k] = db[di - 1][f[di - 1][i][k]][k] + db[di - 1][i][k];
    // start to answer;
    // the problem A;
    int son = 101010101, dom = 1, key;
    for (int i = 1; i <= n; i++)
    {
        pr pt = calc(i, x0);
        if (pt.first * dom < son * pt.second)
            son = pt.first, dom = pt.second, key = i;
    }
    printf("%d\n", key);
    for (int i = 1; i <= m; i++)
    {
        pr ans = calc(si[i], xi[i]);
        printf("%d %d\n", ans.first, ans.second);
    }
    return 0;
}