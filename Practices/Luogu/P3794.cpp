// P3794.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, k, ai[MAX_N], st_or[20][MAX_N], st_gcd[20][MAX_N], log2_[MAX_N];
bool vis_gcd[MAX_N], vis_or[MAX_N];

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int query_gcd(int l, int r)
{
    int len = r - l + 1, g = log2_[len];
    return gcd(st_gcd[g][l], st_gcd[g][r - (1 << g) + 1]);
}

int query_or(int l, int r)
{
    int len = r - l + 1, g = log2_[len];
    return st_or[g][l] | st_or[g][r - (1 << g) + 1];
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), st_or[0][i] = st_gcd[0][i] = ai[i];
    for (int i = 2; i <= n; i++)
        log2_[i] = log2_[i >> 1] + 1;
    for (int i = 1; (1 << i) <= n; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st_or[i][j] = (st_or[i - 1][j] | st_or[i - 1][j + (1 << (i - 1))]);
    for (int i = 1; (1 << i) <= n; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st_gcd[i][j] = gcd(st_gcd[i - 1][j], st_gcd[i - 1][j + (1 << (i - 1))]);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            int int_gcd = query_gcd(i, j), l = j, r = n, gres = 0;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (query_gcd(i, mid) == int_gcd)
                    l = mid + 1, gres = mid;
                else
                    r = mid - 1;
            }
            l = j, r = gres;
            int rres = -1;
            while (l <= r)
            {
                int mid = (l + r) >> 1, or_val = query_or(i, mid);
                if ((or_val ^ int_gcd) == k)
                    rres = mid, l = mid + 1;
                else if (or_val < (k ^ int_gcd))
                    l = mid + 1;
                else if (or_val > (k ^ int_gcd))
                    r = mid - 1;
            }
            l = j, r = gres;
            int lres = 0;
            while (l <= r)
            {
                int mid = (l + r) >> 1, or_val = query_or(i, mid);
                if ((or_val ^ int_gcd) == k)
                    lres = mid, r = mid - 1;
                else if (or_val < (k ^ int_gcd))
                    l = mid + 1;
                else if (or_val > (k ^ int_gcd))
                    r = mid - 1;
            }
            ans += rres - lres + 1;
            j = gres;
        }
    printf("%lld\n", ans);
    return 0;
}