// LOJ2392.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n, K, T, xi[MAX_N];
ll ai[MAX_N];

bool check(int v)
{
    for (int i = 1; i <= n; i++)
        ai[i] = 0LL + xi[i] - 2LL * v * T * i;
    if (ai[1] < ai[n])
        return false;
    int ql = K, qr = K;
    for (int i = K - 1; i >= 1; i--)
        if (ai[i] >= ai[ql])
            ql = i;
    for (int i = K + 1; i <= n; i++)
        if (ai[i] <= ai[qr])
            qr = i;
    int lft = K, rig = K;
    while (lft != ql || rig != qr)
    {
        bool verdict = false;
        int gl = lft, gr = rig;
        while (gl > ql && ai[gl - 1] >= ai[rig])
            if (ai[--gl] >= ai[lft])
                break;
        if (gl < lft && ai[gl] >= ai[lft])
            verdict = true, lft = gl;
        while (gr < qr && ai[gr + 1] <= ai[lft])
            if (ai[++gr] <= ai[rig])
                break;
        if (gr > rig && ai[gr] <= ai[rig])
            verdict = true, rig = gr;
        if (!verdict)
            return false;
    }
    lft = 1, rig = n;
    while (lft != ql || rig != qr)
    {
        bool verdict = false;
        int gl = lft, gr = rig;
        while (gl < ql && ai[gl + 1] >= ai[rig])
            if (ai[++gl] >= ai[lft])
                break;
        if (gl > lft && ai[gl] >= ai[lft])
            verdict = true, lft = gl;
        while (gr > qr && ai[gr - 1] <= ai[lft])
            if (ai[--gr] <= ai[rig])
                break;
        if (gr < rig && ai[gr] <= ai[rig])
            verdict = true, rig = gr;
        if (!verdict)
            return false;
    }
    return true;
}

int main()
{
    scanf("%d%d%d", &n, &K, &T);
    for (int i = 1; i <= n; i++)
        scanf("%d", &xi[i]);
    int l = 0, r = 1e9, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", res);
    return 0;
}