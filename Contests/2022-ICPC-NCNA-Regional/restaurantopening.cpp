// G.cpp
// Team Golden Gopher
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 100;

int n, m;
ll prex[MAX_N], prey[MAX_N];
int cntx[MAX_N], cnty[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            int x;
            scanf("%d", &x);
            prex[i] += x, prey[j] += x;
            cntx[i] += x, cnty[j] += x;
        }
    for (int i = 1; i <= n; i++)
        prex[i] = 1LL * prex[i] * i + prex[i - 1], cntx[i] += cntx[i - 1];
    for (int i = 1; i <= m; i++)
        prey[i] = 1LL * prey[i] * i + prey[i - 1], cnty[i] += cnty[i - 1];
    ll ansx = 0x7fffffffffffffff, ansy = 0x7fffffffffffffff;
    for (int i = 1; i <= n; i++)
        ansx = min(ansx, 1LL * i * cntx[i] - prex[i] + (prex[n] - prex[i]) - 1LL * i * (cntx[n] - cntx[i]));
    for (int i = 1; i <= m; i++)
        ansy = min(ansy, 1LL * i * cnty[i] - prey[i] + (prey[m] - prey[i]) - 1LL * i * (cnty[m] - cnty[i]));
    printf("%lld\n", ansx + ansy);
    return 0;
}