// frontier.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, RANGE = 1.2e6 + 2000;

int task, n, q, ans[MAX_N], qtot[5], anstot, upper, nodes[RANGE], mp[RANGE];

struct query
{
    int typ, x, y, z, val, id;
} queries[5][MAX_N << 1], tmpX[MAX_N << 1], tmpY[MAX_N << 1];

inline char getChar()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

void fileIO()
{
    freopen("frontier.in", "r", stdin);
    freopen("frontier.out", "w", stdout);
}

int read()
{
    int x = 0, f = 1;
    char ch = getChar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getChar();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getChar();
    return x * f;
}

bool cmpX(const query &rhs1, const query &rhs2) { return rhs1.x < rhs2.x || (rhs1.x == rhs2.x && rhs1.typ > rhs2.typ); }

bool cmpRX(const query &rhs1, const query &rhs2) { return rhs1.x > rhs2.x || (rhs1.x == rhs2.x && rhs1.typ > rhs2.typ); }

bool cmpY(const query &rhs1, const query &rhs2) { return rhs1.y < rhs2.y || (rhs1.y == rhs2.y && rhs1.typ > rhs2.typ); }

bool cmpRY(const query &rhs1, const query &rhs2) { return rhs1.y > rhs2.y || (rhs1.y == rhs2.y && rhs1.typ > rhs2.typ); }

int ripe(int x) { return lower_bound(mp + 1, mp + 1 + upper, x) - mp; }

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= upper; x += lowbit(x))
        nodes[x] += d;
}

int querySum(int x, int ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

bool (*f1)(const query &, const query &), (*f2)(const query &, const query &);

void solve2(int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    solve2(l, mid), solve2(mid + 1, r);
    int ytot = 0;
    for (int i = l; i <= r; i++)
        if (i <= mid && tmpX[i].typ > 0)
            tmpY[++ytot] = tmpX[i];
        else if (i > mid && tmpX[i].typ == 0)
            tmpY[++ytot] = tmpX[i];
    sort(tmpY + 1, tmpY + 1 + ytot, f2);

    for (int i = 1; i <= ytot; i++)
        if (tmpY[i].typ > 0)
            update((tmpY[i].z), tmpY[i].val);
        else
            ans[tmpY[i].id] += querySum((tmpY[i].z));
    for (int i = 1; i <= ytot; i++)
        if (tmpY[i].typ > 0)
            update((tmpY[i].z), -tmpY[i].val);
}

void solve1(int typ, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    solve1(typ, l, mid), solve1(typ, mid + 1, r);
    int xtot = 0;
    for (int i = l; i <= r; i++)
        if (i <= mid && queries[typ][i].typ != 0)
            tmpX[++xtot] = queries[typ][i];
        else if (i > mid && queries[typ][i].typ == 0)
            tmpX[++xtot] = queries[typ][i];
    sort(tmpX + 1, tmpX + 1 + xtot, f1), solve2(1, xtot);
}

int main()
{
    fileIO();
    task = read(), n = read(), q = read();
    for (int i = 1, opt, typ, x, y, z; i <= q; i++)
    {
        opt = read();
        if (opt == 1)
        {
            typ = read(), x = read(), y = read(), z = read();
            mp[++mp[0]] = (x), mp[++mp[0]] = (y);
            if (typ == 1)
            {
                queries[typ][++qtot[typ]] = query{typ, x, y, x + y, 1, 0};
                queries[typ][++qtot[typ]] = query{typ, x, y, x + y + z + 1, -1, 0};
                mp[++mp[0]] = (x + y), mp[++mp[0]] = (x + y + z + 1);
            }
            else if (typ == 2)
            {
                queries[typ][++qtot[typ]] = query{typ, x, y, x - y, 1, 0};
                queries[typ][++qtot[typ]] = query{typ, x, y, x + z - y + 1, -1, 0};
                mp[++mp[0]] = (x + z - y + 1), mp[++mp[0]] = (x - y);
            }
            else if (typ == 3)
            {
                queries[typ][++qtot[typ]] = query{typ, x, y, x - y - z, 1, 0};
                queries[typ][++qtot[typ]] = query{typ, x, y, x - y + 1, -1, 0};
                mp[++mp[0]] = (x - y + 1), mp[++mp[0]] = (x - y - z);
            }
            else
            {
                queries[typ][++qtot[typ]] = query{typ, x, y, x + y - z, 1, 0};
                queries[typ][++qtot[typ]] = query{typ, x, y, x + y + 1, -1, 0};
                mp[++mp[0]] = (x + y - z), mp[++mp[0]] = (x + y + 1);
            }
        }
        else
        {
            x = read(), y = read(), anstot++, mp[++mp[0]] = (x), mp[++mp[0]] = (y);
            for (int op = 1; op <= 4; op++)
                queries[op][++qtot[op]] = query{0, x, y, (op == 1 || op == 4) ? x + y : x - y, 0, anstot};
            mp[++mp[0]] = (x + y), mp[++mp[0]] = (x - y);
        }
    }
    sort(mp + 1, mp + 1 + mp[0]), upper = unique(mp + 1, mp + 1 + mp[0]) - mp + 1;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= qtot[i]; j++)
            queries[i][j].z = ripe(queries[i][j].z);
    // solve the typ == 1;
    f1 = cmpX, f2 = cmpY, solve1(1, 1, qtot[1]);
    f1 = cmpX, f2 = cmpRY, solve1(2, 1, qtot[2]);
    f1 = cmpRX, f2 = cmpY, solve1(3, 1, qtot[3]);
    f1 = cmpRX, f2 = cmpRY, solve1(4, 1, qtot[4]);
    for (int i = 1; i <= anstot; i++)
        printf("%d\n", ans[i]);
    return 0;
}