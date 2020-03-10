// LOJ2353.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q[MAX_N], tail;
double Ai[MAX_N], Bi[MAX_N], Ri[MAX_N], dp[MAX_N];

struct node
{
    double x, y;
    int id;
    bool operator<(const node &rhs) const { return x < rhs.x || (fabs(x - rhs.x) < 1e-9 && y < rhs.y); }
} nodes[MAX_N], tmp[MAX_N];

double slope(int i, int j) { return double(nodes[i].y - nodes[j].y) / double(nodes[i].x - nodes[j].x == 0 ? 1e-10 : nodes[i].x - nodes[j].x); }

int binarySearch(double k)
{
    int l = 1, r = tail - 1, res = tail;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (slope(q[mid], q[mid + 1]) <= k)
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    return q[res];
}

void solve(int l, int r)
{
    if (l == r)
    {
        dp[l] = max(dp[l], dp[l - 1]);
        nodes[l].id = l;
        nodes[l].y = dp[l] / double(Ai[l] * Ri[l] + Bi[l]);
        nodes[l].x = Ri[l] * nodes[l].y;
        return;
    }
    int mid = (l + r) >> 1;
    solve(l, mid), tail = 0;
    for (int i = l; i <= mid; i++)
    {
        // maintain its decrease;
        while (tail > 1 && slope(q[tail - 1], q[tail]) <= slope(q[tail - 1], i))
            tail--;
        q[++tail] = i;
    }
    for (int i = mid + 1; i <= r; i++)
    {
        int gpt = nodes[binarySearch(-Ai[i] / Bi[i])].id;
        double VB = 1.0 * dp[gpt] / double(Ai[gpt] * Ri[gpt] + Bi[gpt]);
        dp[i] = max(dp[i], Ai[i] * Ri[gpt] * VB + Bi[i] * VB);
    }
    solve(mid + 1, r);
    int lptr = l, rptr = mid + 1, gptr = l;
    while (lptr <= mid && rptr <= r)
        if (nodes[lptr] < nodes[rptr])
            tmp[gptr++] = nodes[lptr++];
        else
            tmp[gptr++] = nodes[rptr++];
    while (lptr <= mid)
        tmp[gptr++] = nodes[lptr++];
    while (rptr <= r)
        tmp[gptr++] = nodes[rptr++];
    for (int i = l; i <= r; i++)
        nodes[i] = tmp[i];
}

int main()
{
    scanf("%d%lf", &n, &dp[0]);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &Ai[i], &Bi[i], &Ri[i]);
    for (int i = 1; i <= n; i++)
        dp[i] = dp[0];
    solve(1, n), printf("%.3lf\n", dp[n]);
    return 0;
}