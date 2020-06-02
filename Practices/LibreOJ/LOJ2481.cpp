// LOJ2481.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n;
double seq[2][MAX_N], ans;

void solve()
{
    double suma = 0, sumb = 0;
    for (int i = 0, j = 0; i < n; i++)
    {
        suma += seq[0][i];
        while (j < n && sumb < suma)
            sumb += seq[1][j], j++;
        if (sumb < suma)
            break;
        ans = max(ans, suma - i - 1 - j);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf%lf", &seq[0][i], &seq[1][i]);
    sort(seq[0], seq[0] + n, greater<>()), sort(seq[1], seq[1] + n, greater<>());
    solve();
    for (int i = 0; i < n; i++)
        swap(seq[0][i], seq[1][i]);
    solve(), printf("%.4lf\n", ans);
    return 0;
}