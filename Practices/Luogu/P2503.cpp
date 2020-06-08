// P2503.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 22;

int n, m;
double ai[MAX_N], xi[MAX_N];

int main()
{
    scanf("%d%d", &n, &m);
    double avg = 0, ans = 1e18;
    for (int i = 1; i <= n; i++)
        scanf("%lf", &ai[i]), avg += ai[i];
    avg /= 1.0 * m;
    while (1.0 * clock() / CLOCKS_PER_SEC < 0.8)
    {
        random_shuffle(ai + 1, ai + 1 + n);
        memset(xi, 0, sizeof(xi));
        for (int i = 1; i <= n; i++)
            *(min_element(xi + 1, xi + 1 + m)) += ai[i];
        double pans = 0;
        for (int i = 1; i <= m; i++)
            pans += (xi[i] - avg) * (xi[i] - avg);
        pans /= m, ans = min(ans, pans);
    }
    printf("%.2lf\n", sqrt(ans));
    return 0;
}