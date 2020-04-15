// P4696.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, m, pi[MAX_N], hi[MAX_N], lft[MAX_N], rig[MAX_N], pos[MAX_N], pre[MAX_N], nxt[MAX_N], link[MAX_N];

bool check(int *arr, int u, int v) { return arr[v + lft[u]] <= arr[v] && arr[v] <= arr[v + rig[u]]; }

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), pos[pi[i]] = i, pre[i] = i - 1, nxt[i] = i + 1;
    for (int i = 1; i <= m; i++)
        scanf("%d", &hi[i]);
    for (int i = n; i >= 1; i--)
    {
        int u = pos[i];
        if (pre[u])
            lft[i] = pi[pre[u]] - i;
        if (nxt[u] <= n)
            rig[i] = pi[nxt[u]] - i;
        pre[nxt[u]] = pre[u], nxt[pre[u]] = nxt[u];
    }
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j && !check(pos, j + 1, i))
            j = link[j];
        if (check(pos, j + 1, i))
            j++;
        link[i] = j;
    }
    vector<int> vec;
    for (int i = 1, j = 0; i <= m; i++)
    {
        while (j && !check(hi, j + 1, i))
            j = link[j];
        if (check(hi, j + 1, i))
            j++;
        if (j == n)
            vec.push_back(i - n + 1), j = link[j];
    }
    printf("%lld\n", 1LL * vec.size());
    for (int u : vec)
        printf("%d ", u);
    puts("");
    return 0;
}