// UOJ478.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAX_N = 4e5 + 200;

int n, m;
ll A, B, C, X[MAX_N], Y[MAX_N], f[MAX_N], ans = (1LL << 62) - 1 + (1LL << 62);
deque<int> q[MAX_N];
vector<int> dept[MAX_N], recv[MAX_N];

struct trip
{
    int x, y, p, q;
} trips[MAX_N];

ld slope(int i, int j)
{
    if (X[i] == X[j])
        return Y[i] == Y[j] ? 0 : (Y[i] < Y[j] ? 1e99 : -1e99);
    return ld(Y[j] - Y[i]) / ld(X[j] - X[i]);
}

ll pow2(ll x) { return x * x; }

int main()
{
    memset(f, 0x3f, sizeof(f)), f[0] = 0;
    scanf("%d%d%lld%lld%lld", &n, &m, &A, &B, &C);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d%d", &trips[i].x, &trips[i].y, &trips[i].p, &trips[i].q);
        dept[trips[i].p].push_back(i), recv[trips[i].q].push_back(i);
    }
    trips[0] = trip{0, 1, 0, 0}, recv[0].push_back(0);
    for (int T = 0; T <= 1000; T++)
    {
        for (int x : recv[T])
        {
            int y = trips[x].y;
            while (q[y].size() >= 2 && slope(q[y][q[y].size() - 2], q[y].back()) >= slope(q[y].back(), x))
                q[y].pop_back();
            q[y].push_back(x);
            if (trips[x].y == n)
                ans = min(ans, f[x] + trips[x].q);
        }
        for (int x : dept[T])
        {
            int y = trips[x].x;
            while (q[y].size() >= 2 && slope(q[y].front(), q[y][1]) <= trips[x].p)
                q[y].pop_front();
            if (!q[y].empty())
            {
                int head = q[y].front();
                f[x] = f[head] + 1LL * A * pow2(trips[x].p - trips[head].q) + 1LL * B * (trips[x].p - trips[head].q) + C;
            }
            else
                f[x] = 0x3f3f3f3f3f3f3f3f;
            X[x] = 2LL * A * trips[x].q, Y[x] = f[x] + 1LL * A * pow2(trips[x].q) - 1LL * B * trips[x].q + C;
        }
    }
    printf("%lld\n", ans);
    return 0;
}