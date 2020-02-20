// BZ1444.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;
const double eps = 1e-8;

int nodes[MAX_N][26], n, L, m, ptot, fail[MAX_N], tag[MAX_N];
double prob[MAX_N], mat[MAX_N][MAX_N];
char org[MAX_N];
bool endpos[MAX_N];

void insert(char *str, int idx)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - 'A'] == 0)
            nodes[p][str[i] - 'A'] = ++ptot;
        p = nodes[p][str[i] - 'A'];
    }
    endpos[p] = true, tag[idx] = p;
}

void build()
{
    queue<int> q;
    for (int i = 0; i < m; i++)
        if (nodes[0][i])
            q.push(nodes[0][i]);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < m; i++)
            if (nodes[u][i] == 0)
                nodes[u][i] = nodes[fail[u]][i];
            else
            {
                fail[nodes[u][i]] = nodes[fail[u]][i];
                endpos[nodes[u][i]] |= endpos[fail[nodes[u][i]]];
                q.push(nodes[u][i]);
            }
    }
}

bool gauss()
{
    for (int i = 0; i <= ptot; i++)
    {
        int idx = i;
        for (int j = i + 1; j <= ptot; j++)
            if (fabs(mat[j][i]) > fabs(mat[idx][i]))
                idx = j;
        if (fabs(mat[idx][i]) <= eps)
            return false;
        if (idx != i)
            for (int j = i; j <= ptot + 1; j++)
                swap(mat[idx][j], mat[i][j]);
        for (int j = 0; j <= ptot; j++)
            if (i != j)
            {
                double rate = mat[j][i] / mat[i][i];
                for (int k = ptot + 1; k >= i; k--)
                    mat[j][k] -= rate * mat[i][k];
            }
    }
    return true;
}

void output()
{
    for (int i = 0; i <= ptot; i++, puts(""))
        for (int j = 0; j <= ptot + 1; j++)
            printf("%.3lf ", mat[i][j]);
}

int main()
{
    scanf("%d%d%d", &n, &L, &m);
    for (int i = 0, p, q; i < m; i++)
        scanf("%d%d", &p, &q), prob[i] = double(p) / double(q);
    int failure_case = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", org + 1);
        for (int j = 1; org[j] != '\0'; j++)
            if (prob[org[j] - 'A'] < eps)
            {
                failure_case++;
                break;
            }
        insert(org, i);
    }
    if (failure_case == n)
    {
        for (int i = 1; i <= n; i++)
            puts("0.00");
        exit(0);
    }
    build();
    mat[0][0] = mat[0][ptot + 1] = -1.0;
    for (int i = 0; i <= ptot; i++)
    {
        if (i != 0)
            mat[i][i] = -1.0;
        if (endpos[i])
            continue;
        for (int j = 0; j < m; j++)
            mat[nodes[i][j]][i] += prob[j];
    }
    gauss();
    for (int i = 1; i <= n; i++)
    {
        double rate = mat[tag[i]][ptot + 1] / mat[tag[i]][tag[i]];
        if (fabs(rate) < eps)
            puts("0.00");
        else
            printf("%.2lf\n", rate);
    }
    return 0;
}