// CF1283F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef pair<int, int> pii;

int n, ai[MAX_N], bi[MAX_N], deg[MAX_N], fa[MAX_N], max_bit[MAX_N], chk_seq[MAX_N];
priority_queue<pii> q;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &ai[i]), deg[ai[i]]++, max_bit[i] = i;
    max_bit[n] = n;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(make_pair(-max_bit[i], i));
    for (int ptr = n - 1; ptr >= 1; ptr--)
    {
        if (q.empty())
            puts("-1"), exit(0);
        pii u = q.top();
        q.pop();
        fa[u.second] = ai[ptr], max_bit[ai[ptr]] = max(max_bit[ai[ptr]], max_bit[u.second]);
        bi[ptr] = u.second;
        if (--deg[ai[ptr]] == 0)
            q.push(make_pair(-max_bit[ai[ptr]], ai[ptr]));
    }
    q.pop();
    if (!q.empty())
        puts("-1"), exit(0);
    printf("%d\n", ai[1]);
    for (int i = 1; i <= n; i++)
        if (i != ai[1])
            printf("%d %d\n", fa[i], i);
    return 0;
}