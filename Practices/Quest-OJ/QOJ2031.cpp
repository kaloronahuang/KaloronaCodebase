// QOJ2031.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5e5 + 200;

int n, q, stk[MAX_N << 1], tail;
double pos[MAX_N << 1];
ll ai[MAX_N], prefix[MAX_N], constSuf[MAX_N], ans[MAX_N];

struct query
{
    int x, y, id;
    bool operator<(const query &rhs) const { return y < rhs.y; }
} queries[MAX_N];

double calc(int x, int y) { return double(constSuf[y] - constSuf[x]) / double(ai[x] - ai[y]); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &ai[i]), prefix[i] = prefix[i - 1] + ai[i];
        constSuf[i] = ai[i] * i - prefix[i];
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
        scanf("%d%d", &queries[i].x, &queries[i].y), queries[i].id = i;
    sort(queries + 1, queries + 1 + q);
    int curt = 0;
    for (int i = 1; i <= q; i++)
    {
        int delta = queries[i].x - queries[i].y;
        while (curt + 1 <= queries[i].y)
        {
            curt++;
            while (tail > 0 && ai[stk[tail]] >= ai[curt])
                tail--;
            while (tail > 1 && calc(curt, stk[tail]) > calc(stk[tail], stk[tail - 1]))
                tail--;
            stk[++tail] = curt;
            if (tail > 1)
                pos[n - tail] = calc(curt, stk[tail - 1]);
        }
        int idx = n - (lower_bound(pos + n - tail, pos + n - 1, delta) - pos);
        ans[queries[i].id] = delta * ai[stk[idx]] + constSuf[stk[idx]] + prefix[curt];
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}