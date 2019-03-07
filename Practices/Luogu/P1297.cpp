// P1297.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 10000100;
int n, A, B, C, a[MAX_N];
int main()
{
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    for (int i = 2; i <= n; i++)
        a[i] = ((long long)a[i - 1] * A + B) % 100000001;
    for (int i = 1; i <= n; i++)
        a[i] = a[i] % C + 1;
    double ans;
    for (int i = 1; i <= n - 1; i++)
        ans += (1.0 * min(a[i], a[i + 1])) / (1.0 * a[i] * a[i + 1]);
    ans += (1.0 * min(a[n], a[1])) / (1.0 * a[n] * a[1]);
    printf("%.3lf", ans);
    return 0;
}