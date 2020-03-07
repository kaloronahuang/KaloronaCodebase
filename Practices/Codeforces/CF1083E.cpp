// CF1083E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;
const double eps = 1e-10;

typedef pair<int, int> pii;
typedef long long ll;

int n, q[MAX_N];
ll gans, f[MAX_N];

struct node
{
    ll x, y, cost;
    bool operator<(const node &rhs) const { return y > rhs.y; }
} nodes[MAX_N];

double X(int i) { return nodes[i].x; }

double Y(int i) { return f[i]; }

double slope(int i, int j) { return fabs(X(j) - X(i)) < eps ? 1e10 : double(Y(j) - Y(i)) / double(X(j) - X(i)); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld%lld", &nodes[i].x, &nodes[i].y, &nodes[i].cost);
    sort(nodes + 1, nodes + 1 + n);
    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && slope(q[head], q[head + 1]) >= nodes[i].y)
            head++;
        f[i] = 1LL * nodes[i].x * nodes[i].y - nodes[i].cost;
        if (head <= tail)
            f[i] = max(f[i], f[q[head]] + 1LL * (nodes[i].x - nodes[q[head]].x) * nodes[i].y - nodes[i].cost);
        gans = max(gans, f[i]);
        while (head < tail && slope(q[tail - 1], q[tail]) <= slope(q[tail], i))
            tail--;
        q[++tail] = i;
    }
    printf("%lld\n", gans);
    return 0;
}