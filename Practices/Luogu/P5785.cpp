// P5785.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;

int n, q[MAX_N], tail;
ll S, T[MAX_N], coeff[MAX_N], xi[MAX_N], yi[MAX_N], dp[MAX_N];

double slope(int i, int j) { return double(yi[i] - yi[j] + dp[i] - dp[j]) / double(xi[i] - xi[j] == 0 ? 1e-10 : xi[i] - xi[j]); }

int binarySearch(double k)
{
    int l = 1, r = tail - 1, res = tail;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (slope(q[mid], q[mid + 1]) <= k)
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    return q[res];
}

int main()
{
    scanf("%d%lld", &n, &S);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &T[i], &coeff[i]), T[i] += T[i - 1];
    for (int i = n; i >= 1; i--)
        coeff[i] += coeff[i + 1];
    for (int i = 0; i <= n; i++)
        xi[i] = coeff[i + 1];
    for (int i = 0; i <= n; i++)
        yi[i] = coeff[i + 1] * (S - T[i]);
    q[++tail] = 0;
    for (int i = 1; i <= n; i++)
    {
        int gpt = binarySearch(-T[i]);
        dp[i] = dp[gpt] + 1LL * coeff[gpt + 1] * (S + T[i] - T[gpt]);
        while (tail > 1 && slope(q[tail - 1], q[tail]) <= slope(q[tail], i))
            tail--;
        q[++tail] = i;
    }
    printf("%lld\n", dp[n]);
    return 0;
}