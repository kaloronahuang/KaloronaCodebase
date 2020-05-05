// CF1348F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;

int n, ai[MAX_N], bi[MAX_N], seq[MAX_N], pos[MAX_N];
vector<pii> vec[MAX_N];
pii nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

pii pushup(pii ls, pii rs)
{
    if (ls.first == -1)
        return rs;
    if (rs.first == -1)
        return ls;
    return min(ls, rs);
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = make_pair(ai[pos[l]], l));
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = pushup(nodes[lson], nodes[rson]);
}

pii query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pii ls = make_pair(-1, -1), rs = make_pair(-1, -1);
    if (ql <= mid)
        ls = query(ql, qr, l, mid, lson);
    if (mid < qr)
        rs = query(ql, qr, mid + 1, r, rson);
    return pushup(ls, rs);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]), vec[ai[i]].push_back(make_pair(bi[i], i));
    set<pii> st;
    for (int i = 1; i <= n; i++)
    {
        st.insert(vec[i].begin(), vec[i].end());
        seq[st.begin()->second] = i;
        pos[i] = st.begin()->second;
        st.erase(st.begin());
    }
    build(1, n, 1);
    for (int i = 1; i <= n; i++)
    {
        if (i + 1 > bi[pos[i]])
            continue;
        pii res = query(i + 1, bi[pos[i]], 1, n, 1);
        if (res.first <= i)
        {
            puts("NO");
            for (int i = 1; i <= n; i++)
                printf("%d ", seq[i]);
            puts("");
            swap(seq[pos[res.second]], seq[pos[i]]);
            for (int i = 1; i <= n; i++)
                printf("%d ", seq[i]);
            puts("");
            exit(0);
        }
    }
    puts("YES");
    for (int i = 1; i <= n; i++)
        printf("%d ", seq[i]);
    puts("");
    return 0;
}