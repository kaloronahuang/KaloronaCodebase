// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n, k;
double prob[MAX_N], prefix[MAX_N][MAX_N], suffix[MAX_N][MAX_N];

void generateArray()
{
    prefix[0][0] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = 0; j <= i; j++)
            prefix[i][j] = prefix[i - 1][j] * (1.0 - prob[i]) + ((j == 0) ? 0 : prefix[i - 1][j - 1] * prob[i]);
}

int main()
{
	freopen("vote.in", "r", stdin);
	freopen("vote.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &prob[i]);
    sort(prob + 1, prob + 1 + n), generateArray();
    swap(prefix, suffix);
    reverse(prob + 1, prob + 1 + n), generateArray();
    swap(prefix, suffix);
    double ans = 0;
    for (int i = 0; i <= k; i++)
    {
        double tmp = 0;
        for (int j = 0; j <= (k >> 1); j++)
            tmp += prefix[i][j] * suffix[k - i][(k >> 1) - j];
        ans = max(ans, tmp);
    }
    printf("%lf", ans);
    return 0;
}