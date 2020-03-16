// clock.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 100, MAX_C = 110;

typedef pair<int, int> pii;
typedef long long ll;

ll colorTot, n, fight[MAX_C][MAX_C], ai[MAX_N], lft[MAX_N], rig[MAX_N], weight[MAX_N], cost[MAX_N], current_frame;

struct node
{
    int id;
    ll rem;
    bool operator<(const node &rhs) const { return rem < rhs.rem || (rem == rhs.rem && id < rhs.id); }
};

set<node> st;

inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

void process(int pos) { cost[pos] = -fight[ai[pos]][ai[lft[pos]]] - fight[ai[pos]][ai[rig[pos]]]; }

ll calcTime(int x)
{
    if (weight[x] - current_frame * cost[x] <= 0)
        return current_frame;
    if (cost[x] <= 0)
        return 1e18;
    return ((weight[x] - 1) / cost[x] + 1);
}

void update(int pos)
{
    if (pos < 1 || pos > n)
        return;
    st.erase(node{pos, calcTime(pos)});
    weight[pos] -= cost[pos] * current_frame;
    process(pos);
    weight[pos] += cost[pos] * current_frame;
    st.insert(node{pos, calcTime(pos)});
}

int main()
{
    colorTot = read(), n = read();
    for (int i = 1; i <= colorTot; i++)
        for (int j = 1; j <= colorTot; j++)
            fight[i][j] = read();
    for (int i = 1; i <= n; i++)
        ai[i] = read();
    for (int i = 1; i <= n; i++)
    {
        lft[i] = i - 1, rig[i] = i + 1, weight[i] = 1;
        process(i), st.insert(node{i, calcTime(i)});
    }
    while (st.begin()->rem < 1e18)
    {
        auto curt_it = st.begin();
        node curt = *curt_it;
        st.erase(curt_it), current_frame = curt.rem;
        // remove && link;
        lft[rig[curt.id]] = lft[curt.id], rig[lft[curt.id]] = rig[curt.id];
        update(lft[curt.id]), update(rig[curt.id]);
    }
    printf("%lld\n", ai[st.begin()->id]);
    return 0;
}