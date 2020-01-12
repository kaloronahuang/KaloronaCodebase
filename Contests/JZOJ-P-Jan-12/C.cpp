// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;
typedef long long ll;
typedef pair<int, ll> pil;

int n, pi[MAX_N], deg[MAX_N], seq[MAX_N];

void fileIO()
{
    freopen("wall.in", "r", stdin);
    freopen("wall.out", "w", stdout);
}

bool dfs(int pos, int acc)
{
    if (acc < 0)
        return false;
    if (pos == n + 1)
        return true;
    if (seq[pos] != 0)
        return dfs(pos + 1, acc + seq[pos]);
    int x = pos, len = 0, sign = 1;
    while (len == 0 || x != pos)
        seq[x] = sign, x = pi[x], len++, sign = -sign;
    if (dfs(pos + 1, acc + seq[pos]))
        return true;
    x = pos, len = 0, sign = -1;
    while (len == 0 || x != pos)
        seq[x] = sign, x = pi[x], len++, sign = -sign;
    if (dfs(pos + 1, acc + seq[pos]))
        return true;
    seq[pos] = 0;
    return false;
}

int main()
{
    // fileIO();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]);
    for (int i = 1; i <= n; i++)
        if (pi[i] > i && i == pi[pi[i]])
            seq[i] = 1, seq[pi[i]] = -1;
    if (dfs(1, 0))
        for (int i = 1; i <= n; i++)
            if (seq[i] == 1)
                putchar('(');
            else
                putchar(')');
    return 0;
}