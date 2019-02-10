// P2822.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_DOM = 2200;
struct ask
{
    int n, m;
} asks[(int)1e4 + 20];
ll t, k, c_table[MAX_DOM][MAX_DOM], prs[MAX_DOM][MAX_DOM];
int max_dom;
int main()
{
    scanf("%lld%lld", &t, &k);
    c_table[1][1] = c_table[1][0] = 1 % k;
    for (int i = 1; i <= t; i++)
        scanf("%d%d", &asks[i].n, &asks[i].m), max_dom = max(max_dom, max(asks[i].n, asks[i].m));
    for (int i = 2; i <= max_dom; i++)
    {
        c_table[i][0] = 1;
        for (int j = 1; j <= i; j++)
            c_table[i][j] = (c_table[i - 1][j - 1] + c_table[i - 1][j]) % k;
    }
    for (int i = 1; i <= max_dom; i++)
        for (int j = 1; j <= max_dom; j++)
        {
            int res = ((c_table[i][j] == 0 && j <= i) ? 1 : 0);
            prs[i][j] = prs[i - 1][j] + prs[i][j - 1] - prs[i - 1][j - 1] + res;
        }
    for (int i = 1; i <= t; i++)
        printf("%d\n", prs[asks[i].n][min(asks[i].n, asks[i].m)]);
    return 0;
}