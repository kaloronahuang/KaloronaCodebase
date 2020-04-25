// P6186.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, ai[MAX_N], bi[MAX_N], bucket[MAX_N], q;
ll nodes[MAX_N], ans;

inline int lowbit(int x) { return x & (-x); }

void update(int x, ll d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] += d;
}

ll query(int x, ll ret = 0)
{
    for (; x; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ans += (bi[i] = i - 1 - query(ai[i])), bucket[bi[i]]++, update(ai[i], 1);
    memset(nodes, 0, sizeof(nodes));
    // make diff;
    update(1, ans);
    ll pre = 0;
    for (int i = 0; i < n; i++)
        pre += bucket[i], update(i + 2, -(n - pre));
    while (q--)
    {
        int opt, x;
        scanf("%d%d", &opt, &x), x = min(x, n - 1);
        if (opt == 1)
        {
            swap(ai[x], ai[x + 1]), swap(bi[x], bi[x + 1]);
            if (ai[x] > ai[x + 1])
                update(1, 1), update(bi[x + 1] + 2, -1), bi[x + 1]++;
            else
                update(1, -1), bi[x]--, update(bi[x] + 2, 1);
        }
        else
            printf("%lld\n", query(x + 1));
    }
    return 0;
}