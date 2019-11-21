// P4575.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 301;

int T, m, k, mark[MAX_N][2], ptot;
bool mp[MAX_N][MAX_N];

inline char gc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = gc();
    return f * x;
}

int main()
{
    T = read();
    while (T--)
    {
        memset(mp, false, sizeof(mp)), ptot = 0;
        memset(mark, 0, sizeof(mark));
        m = read(), k = read();
        for (int i = 1, u, v; i <= k; i++)
            u = read(), v = read(), mp[++u][++v] = true;
        // checker;
        // to check when a point is connected sufficiently;
        for (int tim = 1; tim <= m; tim++)
            for (int i = 1; i <= m; i++)
            {
                for (int j = 1; j <= m; j++)
                    if (mp[i][j])
                    {
                        if (mark[i][1] == 0 && mark[j][0] != 0)
                            mark[i][1] = mark[j][0];
                        else if (mark[i][1] != 0 && mark[j][0] != mark[i][1] && mark[j][0] != 0)
                        {
                            puts("No");
                            goto loop;
                        }
                    }
                if (mark[i][1] == 0)
                    mark[i][1] = ++ptot;
                for (int j = 1; j <= m; j++)
                    if (mp[i][j])
                        mark[j][0] = mark[i][1];
            }
        // to check sufficienty;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                if (mark[i][1] != 0 && mark[j][0] != 0 && mark[i][1] == mark[j][0] && mp[i][j] == false)
                {
                    puts("No");
                    goto loop;
                }
        puts("Yes");
    loop:
        continue;
    }
    return 0;
}