// P4045.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30, MAX_M = 11, MAX_L = 12;
typedef long long ll;

int n, m, nodes[MAX_M * MAX_L][26], ptot, tag[MAX_M * MAX_L], fail[MAX_M * MAX_L], idx[MAX_M], overlay[MAX_M][MAX_M];
ll dp[MAX_N][1 << MAX_M][MAX_M * MAX_L];
char org[MAX_M][MAX_L];
bool vis[MAX_M];
vector<string> vec;
string tmp;

void insert(char *str, int idx)
{
    int p = 0;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (nodes[p][str[i] - 'a'] == 0)
            nodes[p][str[i] - 'a'] = ++ptot;
        p = nodes[p][str[i] - 'a'];
    }
    tag[p] |= (1 << (idx - 1));
}

void build()
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
            if (nodes[u][i] == 0)
                nodes[u][i] = nodes[fail[u]][i];
            else
            {
                q.push(nodes[u][i]);
                int p = fail[u];
                while (p && nodes[p][i] == 0)
                    p = fail[p];
                fail[nodes[u][i]] = nodes[p][i];
                tag[nodes[u][i]] |= tag[nodes[p][i]];
            }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%s", org[i] + 1), insert(org[i], i);
    build();
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int stat = 0; stat < (1 << m); stat++)
            for (int p = 0; p <= ptot; p++)
                if (dp[i][stat][p] != 0)
                    for (int c = 0; c < 26; c++)
                    {
                        int dst = nodes[p][c];
                        dp[i + 1][stat | tag[dst]][dst] += dp[i][stat][p];
                    }
    ll gans = 0;
    for (int i = 0; i <= ptot; i++)
        gans += dp[n][(1 << m) - 1][i];
    printf("%lld\n", gans);
    if (gans <= 42)
    {
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                if (i != j)
                {
                    int lenx = strlen(org[i] + 1), leny = strlen(org[j] + 1);
                    for (int over = min(lenx, leny); over >= 1; over--)
                    {
                        bool flag = true;
                        for (int ptr = 1; ptr <= over && flag; ptr++)
                            if (org[j][ptr] != org[i][lenx - over + ptr])
                                flag = false;
                        if (flag)
                        {
                            overlay[i][j] = over;
                            break;
                        }
                    }
                }
        for (int i = 1; i <= m; i++)
            idx[i] = i;
        do
        {
            string tmp;
            for (int i = 1; i <= n; i++)
            {
                for (int j = overlay[idx[i - 1]][idx[i]] + 1; org[idx[i]][j] != '\0'; j++)
                    tmp += org[idx[i]][j];
            }
            if (tmp.length() == n)
                vec.push_back(tmp);
        } while (next_permutation(idx + 1, idx + 1 + m));

        sort(vec.begin(), vec.end());
        for (vector<string>::iterator it = vec.begin(); it != vec.end(); it++)
            printf("%s\n", it->c_str());
    }
    return 0;
}