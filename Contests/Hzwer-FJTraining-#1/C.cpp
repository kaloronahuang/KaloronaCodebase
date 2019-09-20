// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100010;

int n, w, ai[MAX_N], bi[MAX_N];
double k, c, ans;

int main()
{
    scanf("%d%lf%lf%d", &n, &k, &c, &w);
    k = 1 - 0.01 * k, c = 1 + 0.01 * c;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &ai[i], &bi[i]);
    for (int i = n; i >= 1; i--)
        if (ai[i] == 1)
            ans = max(ans, ans * k + bi[i]);
        else
            ans = max(ans, ans * c - bi[i]);
    printf("%.2lf", ans * w);
    return 0;
}