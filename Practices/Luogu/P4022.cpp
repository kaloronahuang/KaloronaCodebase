// P4022.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2100000;

struct node
{
    int ch[3], link, dep;
} nodes[MAX_N];

int ptot = 1, last_ptr = 1, n, m, matchLen[MAX_N], dp[MAX_N], q[MAX_N];
char str[MAX_N];

void insert(int c)
{
    int pre = last_ptr, p = last_ptr = ++ptot;
    nodes[p].dep = nodes[pre].dep + 1;
    while (pre && nodes[pre].ch[c] == 0)
        nodes[pre].ch[c] = p, pre = nodes[pre].link;
    if (pre == 0)
        nodes[p].link = 1;
    else
    {
        int q = nodes[pre].ch[c];
        if (nodes[q].dep == nodes[pre].dep + 1)
            nodes[p].link = q;
        else
        {
            int clone = ++ptot;
            nodes[clone] = nodes[q], nodes[clone].dep = nodes[pre].dep + 1;
            nodes[p].link = nodes[q].link = clone;
            while (pre && nodes[pre].ch[c] == q)
                nodes[pre].ch[c] = clone, pre = nodes[pre].link;
        }
    }
}

bool check(int mid)
{
    int head = 1, tail = 0, upper = strlen(str + 1);
    for (int i = 1; i <= mid - 1; i++)
        dp[i] = 0;
    for (int i = mid; i <= upper; i++)
    {
        dp[i] = dp[i - 1];
        while (head <= tail && dp[q[tail]] - q[tail] <= dp[i - mid] - (i - mid))
            tail--;
        q[++tail] = i - mid;
        while (head <= tail && q[head] < i - matchLen[i])
            head++;
        if (head <= tail)
            dp[i] = max(dp[i], dp[q[head]] + i - q[head]);
    }
    return double(dp[upper]) / double(upper) >= 0.9;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", str + 1), last_ptr = 1;
        for (int j = 1; str[j] != '\0'; j++)
            insert(str[j] - '0');
    }
    for (int id = 1; id <= n; id++)
    {
        scanf("%s", str + 1);
        // do the match stuff;
        for (int i = 1, p = 1, clen = 0; str[i] != '\0'; i++)
        {
            int c = str[i] - '0';
            if (nodes[p].ch[c] != 0)
                p = nodes[p].ch[c], clen++;
            else
            {
                while (p && nodes[p].ch[c] == 0)
                    p = nodes[p].link, clen = nodes[p].dep;
                if (p == 0)
                    p = 1, clen = 0;
                else
                    p = nodes[p].ch[c], clen++;
            }
            matchLen[i] = clen;
        }
        check(4);
        int l = 0, r = strlen(str + 1), res;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                l = mid + 1, res = mid;
            else
                r = mid - 1;
        }
        printf("%d\n", res);
    }
    return 0;
}