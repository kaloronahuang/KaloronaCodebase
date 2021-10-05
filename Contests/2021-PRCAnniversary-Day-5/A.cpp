// A.cpp
#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
const int MAX_N = 1e5 + 200;

int n, k, si[MAX_N], ci[MAX_N];

bool check(double score)
{
    vector<double> box;
    for (int i = 1; i <= n; i++)
        box.push_back(1.0 * si[i] * ci[i] - 1.0 * score * si[i]);
    sort(box.begin(), box.end()), reverse(box.begin(), box.end());
    double ans = 0;
    for (int i = 0; i < n - k; i++)
        ans += box[i];
    return (ans > 0);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &si[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    double l = 0, r = 1000, ans = 0;
    while (fabs(r - l) > eps)
    {
        double mid = (r + l) / 2;
        if (check(mid))
            ans = mid, l = mid;
        else
            r = mid;
    }
    printf("%.5lf\n", ans);
    return 0;
}