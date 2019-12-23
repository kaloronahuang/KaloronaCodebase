// LOJ2123.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 202000, INF = 0x3f3f3f3f;

int n1, n2, dp3[MAX_N], dp4[MAX_N];
char strA[MAX_N], strB[MAX_N];

struct node
{
    int ch[26], link, dep;
};

struct SAM
{

    node nodes[MAX_N << 1];

    int last_ptr = 1, ptot = 1;

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
} S2;

struct SSAM
{
    int nodes[MAX_N][26], nxt[26], length;

    void build(char *str)
    {
        length = strlen(str + 1), memset(nxt, -1, sizeof(nxt));
        memset(nodes, -1, sizeof(nodes));
        for (int i = length; i >= 1; i--)
        {
            nxt[str[i] - 'a'] = i;
            for (int c = 0; c < 26; c++)
                nodes[i - 1][c] = nxt[c];
        }
    }
} SS2;

int main()
{
    scanf("%s%s", strA + 1, strB + 1);
    n1 = strlen(strA + 1), n2 = strlen(strB + 1);
    for (int i = 1; i <= n2; i++)
        S2.insert(strB[i] - 'a');
    SS2.build(strB);
    int ans1 = INF, ans2 = INF, ans3 = INF, ans4 = INF;
    // solve the first problem;
    for (int i = 1; i <= n1; i++)
        for (int j = i, p = 1; j <= n2; j++)
        {
            p = S2.nodes[p].ch[strA[j] - 'a'];
            if (p == 0)
            {
                ans1 = min(ans1, j - i + 1);
                break;
            }
        }
    // solve the second problem;
    for (int i = 1; i <= n1; i++)
        for (int j = i, p = 0; j <= n2; j++)
        {
            p = SS2.nodes[p][strA[j] - 'a'];
            if (p == -1)
            {
                ans2 = min(ans2, j - i + 1);
                break;
            }
        }
    // solve the third problem;
    memset(dp3, 0x3f, sizeof(dp3));
    dp3[1] = 0;
    for (int i = 1; i <= n1; i++)
        for (int p = 1; p <= S2.ptot; p++)
        {
            int son = S2.nodes[p].ch[strA[i] - 'a'];
            if (son == 0)
                ans3 = min(ans3, dp3[p] + 1);
            else
                dp3[son] = min(dp3[son], dp3[p] + 1);
        }
    // solve the fourth problem;
    memset(dp4, 0x3f, sizeof(dp4));
    dp4[0] = 0;
    for (int i = 1; i <= n1; i++)
        for (int p = n2; p >= 0; p--)
        {
            int pt = SS2.nodes[p][strA[i] - 'a'];
            if (pt == -1)
                ans4 = min(ans4, dp4[p] + 1);
            else
                dp4[pt] = min(dp4[pt], dp4[p] + 1);
        }
    printf("%d\n%d\n%d\n%d\n", ans1, ans2, ans3, ans4);
    return 0;
}
