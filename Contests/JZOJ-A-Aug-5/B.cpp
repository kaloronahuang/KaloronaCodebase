// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int jump[MAX_N], ptx, pty;
int mp[MAX_N][MAX_N], n, m, q;
char opt[20];

int fix(int pa, int pb) { return (pa % pb + pb) % pb; }

int next_row(int x, int y)
{
    int next_row = -1;
    int max_value = -1;
    for (int rr = x - 1; rr <= x + 1; ++rr)
    {
        const int value = mp[fix(rr, n)][fix(y + 1, m)];
        if (value > max_value)
        {
            max_value = value;
            next_row = rr;
        }
    }
    return next_row;
    /*
    int mx_val = -1, mx_pt = -1;
    for (int i = x - 1; i <= x + 1; i++)
        if (mp[fix(i, n)][fix(y + 1, m)] > mx_val)
            mx_val = mp[fix(i, n)][fix(y + 1, m)], mx_pt = i;
    return mx_pt;
    */
}

int rush(int x, int y)
{
    do
    {
        x = fix(next_row(x, y++), n);
    } while (y < m);
    return x;
}

struct interval
{
    int l = std::numeric_limits<int>::max();
    int r = std::numeric_limits<int>::min();
    bool isCotain(int x) { return l <= x && x <= r; }
    bool isEmpty() { return l > r; }
    int size() { return r - l + 1; }
};

void update(int x, int y)
{
    const int target_row = rush(x, y);
    interval rows;
    rows.l = rows.r = x;
    int cc = y;
    while (cc > 0)
    {
        --cc;
        interval new_rows;
        for (int rr = rows.l - 1; rr <= rows.l + 1; ++rr)
        {
            if (rows.isCotain(next_row(rr, cc)))
            {
                new_rows.l = rr;
                break;
            }
        }
        for (int rr = rows.r + 1; rr >= rows.r - 1; --rr)
        {
            if (rows.isCotain(next_row(rr, cc)))
            {
                new_rows.r = rr;
                break;
            }
        }
        if (new_rows.isEmpty())
            return;
        rows = new_rows;
    }
    if (rows.size() >= n)
        for (int rr = 0; rr < n; ++rr)
            jump[rr] = target_row;
    else
        for (int rr = rows.l; rr <= rows.r; ++rr)
            jump[fix(rr, n)] = target_row;
    return;
    /*
    int ans = rush(x, y);
    interval current;
    current.l = current.r = x;
    int remain = y;
    while (remain > 0)
    {
        remain--;
        interval newone;
        for (int i = current.l - 1; i <= current.l + 1; i++)
            if (current.isCotain(next_row(i, remain)))
            {
                newone.l = i;
                break;
            }
        for (int i = current.r + 1; i >= current.r - 1; i--)
            if (current.isCotain(next_row(i, remain)))
            {
                newone.r = i;
                break;
            }
        if (newone.isEmpty())
            return;
        current = newone;
    }
    if (current.size() >= n)
        for (int i = 0; i < n; i++)
            jump[i] = ans;
    else
        for (int i = current.l; i <= current.r; i++)
            jump[fix(i, n)] = ans;
    */
}

void move(int steps)
{
    static int walk_id = 0;
    static int last_walk_id[MAX_N];
    static int last_k[MAX_N];
    walk_id++;

    if (steps >= m - pty)
    {
        steps -= (m - pty);
        ptx = rush(ptx, pty), pty = 0;
    }
    while (steps >= m)
    {
        steps -= m;
        ptx = jump[ptx];

        if (last_walk_id[ptx] == walk_id)
        {
            const int cycle_len = last_k[ptx] - steps;
            if (steps >= cycle_len)
            {
                const int n_cycles = steps / cycle_len;
                steps -= n_cycles * cycle_len;
            }
        }
        last_walk_id[ptx] = walk_id;
        last_k[ptx] = steps;
    }
    while (steps--)
        ptx = fix(next_row(ptx, pty++), n);
}

int main()
{
    /*
    freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
    */
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &mp[i][j]);
    scanf("%d", &q);
    for (int i = 0; i < n; i++)
        jump[i] = rush(i, 0);
    while (q--)
    {
        int a, b, c;
        scanf("%s%d", opt + 1, &a);
        if (opt[1] == 'm')
            move(a), printf("%d %d\n", ptx + 1, pty + 1);
        else
        {
            scanf("%d%d", &b, &c);
            a--, b--;
            mp[a][b] = c;
            for (int i = a - 1; i <= a + 1; i++)
                update(fix(i, n), fix(b - 1, m));
        }
    }
    return 0;
}