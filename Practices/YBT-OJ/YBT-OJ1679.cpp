// YBT-OJ1679.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 200;

int n, seq[MAX_N];
ll prefix[MAX_N];

double calc(int pos, int len) { return double(prefix[n] - prefix[n - len] + prefix[pos] - prefix[pos - len - 1]) / double((len << 1) | 1); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    sort(seq + 1, seq + 1 + n);
    for (int i = 1; i <= n; i++)
        prefix[i] = 1LL * prefix[i - 1] + seq[i];
    // odd one;
    double gans = 0;
    for (int i = 2; i <= n - 1; i++)
    {
        int l = 1, r = min(n - i, i - 1);
        double pans = seq[i];
        while (l <= r)
        {
            int len = (l + r) >> 1;
            double tmp = calc(i, len);
            double cp = calc(i, len - 1);
            if (tmp - cp > -double(1e-8))
                pans = tmp, l = len + 1;
            else
                r = len - 1;
        }
        gans = max(gans, pans - seq[i]);
    }
    printf("%.5lf\n", gans);
    return 0;
}