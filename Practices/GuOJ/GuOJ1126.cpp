// GuOJ1126.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_S = 18, mod = 998244353;

int n, m, q, s, seq[MAX_N], idx[MAX_S], rk[MAX_S], ptot;
int ch[MAX_N][2], fail[MAX_N];
bool tag[MAX_N];
char str[MAX_N];

struct matrix
{
    int mat[MAX_S][MAX_S];

    int *operator[](const int &rhs) { return mat[rhs]; }
    void clear() { memset(mat, 0, sizeof(mat)); }
    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 0; i <= s; i++)
            for (int k = 0; k <= s; k++)
                if (mat[i][k])
                    for (int j = 0; j <= s; j++)
                        if (rhs.mat[k][j])
                            ret[i][j] = (0LL + ret[i][j] + 1LL * mat[i][k] * rhs.mat[k][j] % mod) % mod;
        return ret;
    }
} nodes[MAX_N << 2], t1, t0, tr;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
    {
        if (seq[l] == -1)
            nodes[p] = tr;
        else if (seq[l] == 0)
            nodes[p] = t0;
        else
            nodes[p] = t1;
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = nodes[lson] * nodes[rson];
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        if (val == 0)
            nodes[p] = t0;
        else if (val == 1)
            nodes[p] = t1;
        else
            nodes[p] = tr;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    nodes[p] = nodes[lson] * nodes[rson];
}

matrix query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    bool tag1 = ql <= mid, tag2 = mid < qr;
    if (tag1 && tag2)
        return query(ql, qr, l, mid, lson) * query(ql, qr, mid + 1, r, rson);
    if (tag1)
        return query(ql, qr, l, mid, lson);
    else
        return query(ql, qr, mid + 1, r, rson);
}

void insert()
{
    int len = strlen(str + 1), p = 0;
    for (int i = 1; i <= len; i++)
    {
        if (ch[p][str[i] - '0'] == 0)
            ch[p][str[i] - '0'] = ++ptot;
        p = ch[p][str[i] - '0'];
    }
    tag[p] = true;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < 2; i++)
        if (ch[0][i])
            q.push(ch[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 2; i++)
            if (ch[u][i] == 0)
                ch[u][i] = ch[fail[u]][i];
            else
            {
                fail[ch[u][i]] = ch[fail[u]][i];
                tag[ch[u][i]] |= tag[fail[ch[u][i]]];
                q.push(ch[u][i]);
            }
    }
}

int main()
{
    // ptot = 2, ch[0][0] = 1, ch[0][1] = 2;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1; i <= m; i++)
        scanf("%s", str + 1), insert();
    build();
    for (int i = 0; i <= ptot; i++)
        if (!tag[i])
            idx[++s] = i, rk[i] = s;
    for (int i = 0; i <= s; i++)
    {
        int id = idx[i], lc = rk[ch[id][0]], rc = rk[ch[id][1]];
        if (tag[id])
            continue;
        if (!tag[ch[id][0]])
            tr[i][lc]++, t0[i][lc]++;
        if (!tag[ch[id][1]])
            tr[i][rc]++, t1[i][rc]++;
    }
    build(1, n, 1);
    while (q--)
    {
        int x, y;
        scanf("%s%d%d", str + 1, &x, &y);
        if (str[1] == 'Q')
        {
            matrix src = query(x, y, 1, n, 1);
            int ans = 0;
            for (int i = 0; i <= s; i++)
                ans = (0LL + ans + src[0][i]) % mod;
            printf("%d\n", ans);
        }
        else
        {
            update(x, 1, n, 1, y);
            seq[x] = y;
        }
    }
    return 0;
}