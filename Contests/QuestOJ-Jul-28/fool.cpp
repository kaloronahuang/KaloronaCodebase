// fool.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MAX_N = 4e5 + 200;

int n, q, tlen, match[MAX_N], ansBox[MAX_N];
char S[MAX_N], T[MAX_N];
vector<pii> queries[2][MAX_N];
vector<int> pts[MAX_N];

struct BIT
{
    ll nodes[MAX_N << 1];

    inline int lowbit(int x) { return x & (-x); }

    void clear()
    {
        for (int i = 0; i <= tlen; i++)
            nodes[i] = 0;
    }

    void update(int x, int d)
    {
        for (; x <= tlen; x += lowbit(x))
            nodes[x] += d;
    }

    ll query(int x)
    {
        ll ret = 0;
        for (; x; x -= lowbit(x))
            ret += nodes[x];
        return ret;
    }
} tr[2];

void manacher()
{
    T[++tlen] = '{', T[++tlen] = '|';
    for (int i = 1; i <= n; i++)
        T[++tlen] = S[i], T[++tlen] = '|';
    T[++tlen] = '}';
    int rig = 0, pt = 0;
    for (int i = 1; i <= tlen; i++)
    {
        if (rig > i)
            match[i] = min(match[2 * pt - i], rig - i);
        else
            match[i] = 1;
        while (i - match[i] >= 1 && T[i + match[i]] == T[i - match[i]])
            match[i]++;
        if (i + match[i] > rig)
            rig = i + match[i], pt = i;
    }
}

void iteratingLeft()
{
    tr[0].clear(), tr[1].clear();
    for (int i = 1; i <= tlen; i++)
        pts[i].clear();
    for (int l = tlen; l >= 1; l--)
    {
        tr[0].update(l, 1), tr[1].update(l, l + 1);
        if (l - match[l] + 1 >= 1)
            pts[l - match[l] + 1].push_back(l);
        for (int x : pts[l])
            tr[0].update(x, -1), tr[1].update(x, match[x] - (x + 1));
        for (pii x : queries[0][l])
        {
            int p = x.first, q = x.second;
            ansBox[q] += tr[1].query(p) - 1LL * l * tr[0].query(p);
        }
    }
}

void iteratingRight()
{
    tr[0].clear(), tr[1].clear();
    for (int i = 1; i <= tlen; i++)
        pts[i].clear();
    for (int r = 1; r <= tlen; r++)
    {
        tr[0].update(r, 1), tr[1].update(r, -r + 1);
        if (r + match[r] - 1 <= tlen)
            pts[r + match[r] - 1].push_back(r);
        for (int x : pts[r])
            tr[0].update(x, -1), tr[1].update(x, match[x] - (-x + 1));
        for (pii x : queries[1][r])
        {
            int p = x.first, q = x.second;
            ansBox[q] += (tr[1].query(r) - tr[1].query(p - 1)) + 1LL * r * (tr[0].query(r) - tr[0].query(p - 1));
        }
    }
}

int main()
{
    scanf("%d%d%s", &n, &q, S + 1), manacher();
    for (int i = 1, l, r; i <= q; i++)
    {
        scanf("%d%d", &l, &r);
        // first to add the special characters positions to the answer;
        ansBox[i] = -(r - l + 2);
        l <<= 1, r = (r + 1) << 1;
        int mid = (l + r) >> 1;
        queries[0][l].push_back(make_pair(mid, i));
        queries[1][r].push_back(make_pair(mid + 1, i));
    }
    iteratingLeft(), iteratingRight();
    for (int i = 1; i <= q; i++)
        printf("%d\n", ansBox[i] >> 1);
    return 0;
}