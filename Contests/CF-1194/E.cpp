// E.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<int, int>

using namespace std;

const int MAX_N = 10005, Dom = 5001;

vector<pr> vertical[MAX_N], horizontial[MAX_N];
vector<int> tag[MAX_N];
int tree[MAX_N], n;

inline int lowbit(int x) { return x & -x; }

void update(int pos, int x)
{
    for (; pos < MAX_N; pos += lowbit(pos))
        tree[pos] += x;
}

int sum(int pos)
{
    int ans = 0;
    for (; pos > 0; pos -= lowbit(pos))
        ans += tree[pos];
    return ans;
}

int sum(int l, int r) { return sum(r) - sum(l - 1); }

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        x1 += Dom, y1 += Dom, x2 += Dom, y2 += Dom;
        if (x1 == x2)
            vertical[x1].push_back(make_pair(min(y1, y2), max(y1, y2)));
        else
            horizontial[y1].push_back(make_pair(min(x1, x2), max(x1, x2)));
    }
    ll ans = 0;
    for (int y = 0; y < MAX_N; y++)
        for (auto s : horizontial[y])
        {
            memset(tree, 0, sizeof(tree));
            for (int i = 0; i < MAX_N; i++)
                tag[i].clear();
            int l = s.first, r = s.second;
            for (int x = l; x <= r; x++)
                for (auto s_ : vertical[x])
                    if (s_.first <= y && s_.second > y)
                    {
                        tag[s_.second].push_back(x);
                        update(x, 1);
                    }
            for (int y2 = y + 1; y2 < MAX_N; y2++)
            {
                for (auto s_ : horizontial[y2])
                {
                    int cur = sum(s_.first, s_.second);
                    ans += (cur) * (cur - 1);
                }
                for (auto rm : tag[y2])
                    update(rm, -1);
            }
        }
    printf("%lld", ans >> 1);
    return 0;
}