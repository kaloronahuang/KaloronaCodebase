// ARC085C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int n, m;

int main()
{
    scanf("%d%d", &n, &m);
    int ct = 1LL * m * 1900 + 1LL * (n - m) * 100;
    double ans = 0, bas = 1.0 - 1.0 / double(1LL << m), acc = 1.0 / double(1LL << m);
    for (int i = 1; i <= 100000; i++)
        ans += ct * i * acc, acc *= bas;
    printf("%.0lf\n", ans);
    return 0;
}