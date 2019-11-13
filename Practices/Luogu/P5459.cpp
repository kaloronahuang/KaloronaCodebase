// P5459.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e5 + 200;

int n, seq[MAX_N], L, R;
ll prefix[MAX_N], ans;

void cdq(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int lbound = l, rbound = l - 1;
    for (int rig = mid + 1; rig <= r; rig++)
    {
        while (rbound + 1 <= mid && prefix[rig] - prefix[rbound + 1] >= L)
            rbound++;
        while (lbound <= mid && prefix[rig] - prefix[lbound] > R)
            lbound++;
        ans += rbound - lbound + 1;
    }
    sort(prefix + l, prefix + r + 1);
}

int main()
{
    scanf("%d%d%d", &n, &L, &R);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), prefix[i] = prefix[i - 1] + seq[i];
    cdq(0, n), printf("%lld", ans);
    return 0;
}