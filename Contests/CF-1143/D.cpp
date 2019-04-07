// D.cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, a, b;
int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
int main()
{
    scanf("%d%d%d%d", &n, &k, &a, &b);
    int s = 1 + a;
    int ans1 = 0x3f3f3f3f, ans2 = 0;
    for (int i = 1; i <= n; i++)
    {
        int l = k * i + (a - b);
    }
    return 0;
}