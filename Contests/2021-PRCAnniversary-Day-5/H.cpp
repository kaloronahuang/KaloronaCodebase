// H.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;

int n, ai[MAX_N];
ll nodes[MAX_N];
bool bookmark[MAX_N];
vector<int> mp;

inline int lowbit(int x) { return x & (-x); }

void update(int x, ll d)
{
    for (; x <= n; x += lowbit(x))
        nodes[x] += d;
}

ll query(int x)
{
    ll ret = 0;
    for (; x >= 1; x -= lowbit(x))
        ret += nodes[x];
    return ret;
}

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

vector<int> answer;

void solve(int start_pos, ll acc)
{
    if (start_pos == n + 1)
    {
        if (acc != 0)
            puts("-1");
        return;
    }
    int pt = start_pos;
    for (; pt <= n; pt++)
    {
        ll cdp = query(pt) + 1;
        if (cdp > acc)
            break;
        update(pt, cdp);
    }
    pt--;
    ll cdp = query(pt) + 1;
    if (cdp > acc)
        puts("-1");
    else
    {
        acc -= cdp, answer
    }
}

int main()
{
    ll acc;
    scanf("%d%lld", &n, &acc);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), mp.push_back(ai[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    solve(1, acc);
    return 0;
}