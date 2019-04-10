// CH4401.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 40100;
vector<int> poses[MAX_N];
int arr[MAX_N], mapping[MAX_N], lft[MAX_N], tot, rig[MAX_N], cnt[MAX_N], mode[900][900], affiliate[MAX_N];
int find(int x, int l, int r)
{
    return upper_bound(poses[x].begin(), poses[x].end(), r) - lower_bound(poses[x].begin(), poses[x].end(), l);
}
void judge(int x, int l, int r, int &ans, int &ct)
{
    int w = find(x, l, r);
    if (w > ct || (w == ct && x < ans))
        ct = w, ans = x;
}
int query(int l, int r)
{
    int ans = 0, ct = 0;
    int p = affiliate[l], q = affiliate[r];
    if (p == q)
    {
        for (int i = l; i <= r; i++)
            judge(arr[i], l, r, ans, ct);
        return mapping[ans];
    }
    int x = 0, y = 0;
    if (p + 1 <= q - 1)
        x = p + 1, y = q - 1;
    for (int i = l; i <= rig[p]; i++)
        judge(arr[i], l, r, ans, ct);
    for (int i = lft[q]; i <= r; i++)
        judge(arr[i], l, r, ans, ct);
    if (mode[x][y])
        judge(mode[x][y], l, r, ans, ct);
    return mapping[ans];
}
int main()
{
    int n, m, t, len;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), mapping[++tot] = arr[i];
    sort(mapping + 1, mapping + 1 + n);
    tot = unique(mapping + 1, mapping + 1 + n) - (mapping + 1);
    for (int i = 1; i <= n; i++)
        arr[i] = lower_bound(mapping + 1, mapping + 1 + tot, arr[i]) - mapping, poses[arr[i]].push_back(i);
    t = sqrt(log(n) / log(2) * n);
    len = t ? n / t : n;
    for (int i = 1; i <= t; i++)
        lft[i] = (i - 1) * len + 1, rig[i] = i * len;
    if (rig[t] < n)
        lft[t + 1] = rig[t] + 1, rig[++t] = n;
    for (int i = 1; i <= t; i++)
        for (int j = lft[i]; j <= rig[i]; j++)
            affiliate[j] = i;
    memset(mode, 0, sizeof(mode));
    for (int i = 1; i <= t; i++)
    {
        memset(cnt, 0, sizeof(cnt));
        int ct = 0, ans = 0;
        for (int j = lft[i]; j <= n; j++)
        {
            if (++cnt[arr[j]] > ct || (cnt[arr[j]] == ct && arr[j] < ans))
                ans = arr[j], ct = cnt[arr[j]];
            mode[i][affiliate[j]] = ans;
        }
    }
    int last = 0;
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r), l = (l + last - 1) % n + 1, r = (r + last - 1) % n + 1;
        if (l > r)
            swap(l, r);
        last = query(l, r);
        printf("%d\n", last);
    }
    return 0;
}