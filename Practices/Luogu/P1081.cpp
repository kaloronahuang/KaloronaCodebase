// P1081.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>
using namespace std;
const int MAX_N = 100010, INF = 0x3f3f3f3f;

int n, m, hi[MAX_N], xi[MAX_N], si[MAX_N], ga[MAX_N];
int gb[MAX_N], w, f[20][MAX_N][2], da[20][MAX_N][2];
int db[20][MAX_N][2];

multiset<pr> bst;
multiset<pr>::iterator it, it1, it2, it3, it4;

pr calc(int s, int x)
{
    int la = 0, lb = 0;
    int p = s;
    for (int i = 19; i >= 0; i--)
        if (f[i][p][0] && la + lb + da[i][p][0] + db[i][p][0] <= x)
            la += da[i][p][0], lb += db[i][p][0],
                p = f[i][p][0];
    return make_pair(la, lb);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &hi[i]);
    scanf("%d%d", &xi[0], &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &si[i], &xi[i]);
    bst.insert(make_pair(INF, 0)), bst.insert(make_pair(-INF, 0));
    bst.insert(make_pair(INF, 0)), bst.insert(make_pair(-INF, 0));
    for (int i = n; i >= 1; i--)
    {
        bst.insert(make_pair(hi[i], i));
        it = bst.find(make_pair(hi[i], i));
        it1 = (++it), it2 = (++it);
        it3 = (--(--(--it))), it4 = (--it);
        int a = (*it3).first != -INF ? hi[i] - (*it3).first : INF;
        int b = (*it1).first != INF ? (*it1).first - hi[i] : INF;
        if (a <= b)
        {
            gb[i] = (*it3).second;
            a = (*it4).first != -INF ? hi[i] - (*it4).first : INF;
            ga[i] = (a <= b ? (*it4).second : (*it1).second);
        }
        else
        {
            gb[i] = (*it1).second;
            b = (*it2).first != INF ? (*it2).first - hi[i] : INF;
            ga[i] = (a <= b ? (*it3).second : (*it2).second);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        f[0][i][0] = ga[i];
        f[0][i][1] = gb[i];
    }
    for (int i = 1; i <= n; i++)
        f[1][i][0] = f[0][f[0][i][0]][1],
        f[1][i][1] = f[0][f[0][i][1]][0];
    for (int i = 2; i < 19; i++)
        for (int j = 1; j <= n; j++)
            f[i][j][0] = f[i - 1][f[i - 1][j][0]][0],
            f[i][j][1] = f[i - 1][f[i - 1][j][1]][1];
    for (int i = 1; i <= n; i++)
    {
        da[0][i][0] = abs(hi[i] - hi[ga[i]]);
        db[0][i][1] = abs(hi[i] - hi[gb[i]]);
        da[0][i][1] = db[0][i][0] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        da[1][i][0] = da[0][i][0];
        da[1][i][1] = da[0][f[0][i][1]][0];
        db[1][i][0] = db[0][f[0][i][0]][1];
        db[1][i][1] = db[0][i][1];
    }
    for (int i = 2; i < 19; i++)
        for (int j = 1; j <= n; j++)
        {
            da[i][j][0] = da[i - 1][j][0] + da[i - 1][f[i - 1][j][0]][0];
            da[i][j][1] = da[i - 1][j][1] + da[i - 1][f[i - 1][j][1]][1];
            db[i][j][0] = db[i - 1][j][0] + db[i - 1][f[i - 1][j][0]][0];
            db[i][j][1] = db[i - 1][j][1] + db[i - 1][f[i - 1][j][1]][1];
        }
    pr ans = calc(1, xi[0]);
    int la = ans.first, lb = ans.second;
    double ans1[2] = {1, (lb ? (double)la / lb : INF)};
    for (int i = 2; i <= n; i++)
    {
        ans = calc(i, xi[0]);
        la = ans.first, lb = ans.second;
        if ((double)la / lb < ans1[1] || (((double)la / lb == ans1[1]) && hi[i] > hi[(int)ans1[0]]))
        {
            ans1[0] = i;
            ans1[1] = (double)la / lb;
        }
    }
    printf("%d\n", (int)ans1[0]);
    for (int i = 1; i <= m; i++)
        ans = calc(si[i], xi[i]), printf("%d %d\n", ans.first, ans.second);
    return 0;
}