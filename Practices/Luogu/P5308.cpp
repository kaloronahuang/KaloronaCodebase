// P5308.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long double db;
typedef pair<db, int> pdi;

const int MAX_N = 1e5 + 200;
const db eps = 1e-12;

int n, k, q[MAX_N], g[MAX_N];
db f[MAX_N];

db slope(int i, int j) { return db(f[i] - f[j]) / db(i - j); }

bool check(db weight)
{
    int head = 1, tail = 0;
    q[++tail] = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = g[i] = 0;
        while (head < tail && 1.0 * slope(q[head], q[head + 1]) >= 1.0 / db(i))
            head++;
        f[i] = f[q[head]] + db(i - q[head]) / db(i) - weight, g[i] = g[q[head]] + 1;
        // printf("trans %d -> %d : %.9Lf\n", q[head], i, f[i]);
        while (head < tail && slope(q[tail], i) >= slope(q[tail - 1], q[tail]))
            tail--;
        q[++tail] = i;
    }
    // printf("%.9Lf %d\n", f[n], g[n]);
    return g[n] >= k;
}

int main()
{
    scanf("%d%d", &n, &k);
    if (n == k)
    {
        db ans = 0;
        for (int i = 1; i <= n; i++)
            ans += db(1) / db(n - i + 1);
        printf("%.9Lf\n", ans);
        return 0;
    }
    db l = 0, r = 1e9, res = 0;
    while (fabs(r - l) > eps)
    {
        db mid = (l + r) / 2.0;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    check(l), printf("%.9Lf\n", f[n] + 1.0 * l * k);
    return 0;
}