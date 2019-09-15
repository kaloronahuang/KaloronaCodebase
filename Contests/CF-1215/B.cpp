// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, arr[MAX_N];

int main()
{
    scanf("%d", &n);
    long long ans1 = 0, ans2 = 0;
    for (int i = 1, tot = 0; i <= n; i++)
        scanf("%d", &arr[i]);
    int tot1 = 1, tot2 = 0;
    for (int i = 1, opt = 1; i <= n; i++)
    {
        if (arr[i] < 0)
            opt *= -1;
        if (opt == 1)
            ans1 += tot1, tot1++, ans2 += tot2;
        else
            ans1 += tot2, tot2++, ans2 += tot1;
    }
    printf("%lld %lld\n", ans2, ans1);
    return 0;
}