// P3564.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e6 + 200;

int n, ai[MAX_N], pre[MAX_N], head[MAX_N];
char str[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N];

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%s", &n, str + 1);
    int base = 0;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + (str[i] == 'p' ? 1 : -1), base = min(base, pre[i]);
    for (int i = n; i >= 0; i--)
        edges[i].to = i, edges[i].nxt = head[pre[i] - base], head[pre[i] - base] = i;
    int ans = 0;
    for (int i = n, ptr = n; i >= 1; i--)
        if (str[i] == 'j')
            ptr = i - 1;
        else
        {
            if (edges[i - 1].nxt != -1 && pre[edges[edges[i - 1].nxt].to] >= pre[ptr])
                ptr = edges[edges[i - 1].nxt].to;
            edges[i - 1].to = ptr;
            ans = max(ans, ptr - i + 1);
        }
    printf("%d\n", ans);
    return 0;
}