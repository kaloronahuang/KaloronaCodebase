// P3502.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, ptot, nodes[MAX_N][26], tag[MAX_N], fail[MAX_N], len[MAX_N], pos[MAX_N];
int dep[MAX_N];
char opt[MAX_N];

struct matrix
{
    ll mat[210][210];

    void clear() { memset(mat, 0x3f, sizeof(mat)); }

    ll *operator[](const int &idx) { return mat[idx]; }

    matrix operator*(const matrix &rhs)
    {
        matrix ret;
        ret.clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    ret[i][j] = min(ret[i][j], mat[i][k] + rhs.mat[k][j]);
        return ret;
    }

    matrix operator^(const int &rhs)
    {
        int tim = rhs;
        matrix ret, bas = *this;
        ret.clear();
        for (int i = 1; i <= n; i++)
            ret[i][i] = 0;
        while (tim)
        {
            if (tim & 1)
                ret = ret * bas;
            bas = bas * bas;
            tim >>= 1;
        }
        return ret;
    }
} A;

void insert(char *str, int id)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - 'a'] == 0)
            nodes[p][str[i] - 'a'] = ++ptot;
        p = nodes[p][str[i] - 'a'];
    }
    tag[p] = id, pos[id] = p;
}

void bfs()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (nodes[0][i])
            q.push(nodes[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
            if (nodes[u][i])
            {
                int k = fail[u];
                while (nodes[k][i] == 0 && k)
                    k = fail[k];
                fail[nodes[u][i]] = nodes[k][i], q.push(nodes[u][i]);
            }
    }
}

int main()
{
    scanf("%d%d", &n, &m), A.clear();
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", opt + 1), len[i] = strlen(opt + 1), insert(opt, i);
        for (int j = 1; j <= n; j++)
            A[j][i] = len[i];
    }
    bfs();
    for (int i = 1; i <= n; i++)
        for (int j = pos[i]; fail[j]; j = fail[j])
        {
            queue<int> q;
            dep[fail[j]] = 0, q.push(fail[j]);
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int c = 0; c < 26; c++)
                    if (nodes[u][c])
                        A[i][tag[nodes[u][c]]] = dep[nodes[u][c]] = dep[u] + 1, q.push(nodes[u][c]);
            }
        }
    A = A ^ (m - 1);
    ll ans = 0x7fffffffffffffff;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans = min(ans, len[i] + A[i][j]);
    printf("%lld\n", ans);
    return 0;
}