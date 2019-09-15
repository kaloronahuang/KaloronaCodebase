#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a1, a2, k1, k2, n;
    scanf("%d%d%d%d%d", &a1, &a2, &k1, &k2, &n);
    int temp1 = a1 * (k1 - 1) + a2 * (k2 - 1);
    printf("%d ", max(0, n - temp1));
    if (k1 > k2)
        swap(a1, a2), swap(k1, k2);
    int ans = 0;
    if (a1 * k1 <= n)
        printf("%d", a1 + (n - k1 * a1) / k2);
    else
        printf("%d", n / k1);
    return 0;
}