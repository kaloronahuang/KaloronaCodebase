// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int n, m, cnt[MAX_N];
pair<int, int> ints[MAX_N], segs[MAX_N];
bool tag[MAX_N];

bool compare(pair<int, int> pa, pair<int, int> pb) { return pa.first < pb.first; }

int main()
{
    freopen("raining.in", "r", stdin);
    freopen("raining.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ints[i].first, &ints[i].second);
    for (int i = 1, a, b, w; i <= m; i++)
        scanf("%d%d%d", &a, &b, &w), cnt[a] += b * w;
    sort(ints + 1, ints + 1 + n, compare);
    int ans = 0, j = n;
    for (int i = 5000; i >= 1; i--)
    {
        for (; j >= 1 && cnt[i] > 0; j--)
            if (tag[j] == false && ints[j].first <= i && i <= ints[j].second)
                tag[j] = true, ans += i, cnt[i]--;
    }
    printf("%d", ans);
    return 0;
}