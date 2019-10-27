// time.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200, DOM = 1e5;

int nodes[MAX_N], n, seq[MAX_N];
ll prefix[MAX_N], suffix[MAX_N];

inline int lowbit(int x) { return x & (-x); }

void update(int x, int d)
{
    for (; x <= DOM; x += lowbit(x))
        nodes[x] += d;
}

int query(int x)
{
    int ans = 0;
    for (; x; x -= lowbit(x))
        ans += nodes[x];
    return ans;
}

int main()
{
    scanf("%d", &n);
    int mx = 0, id;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &seq[i]);
        if (seq[i] > mx)
            mx = seq[i], id = i;
    }
    for (int i = 1; i <= n; i++)
        if (i != id)
            prefix[i] = prefix[i - 1] + ((i - 1) - query(seq[i])), update(seq[i], 1);
        else
            prefix[i] = prefix[i - 1];
    memset(nodes, 0, sizeof(nodes));
    for (int i = n; i >= 1; i--)
        if (i != id)
            suffix[i] = suffix[i + 1] + ((n - i) - query(seq[i])), update(seq[i], 1);
        else
            suffix[i] = suffix[i + 1];
    ll ans = prefix[id - 1] + suffix[id + 1];

    for (int peak = 1; peak <= n + 1; peak++)
        ans = min(ans, prefix[peak - 1] + suffix[peak]);
    printf("%lld", ans);
    return 0;
}