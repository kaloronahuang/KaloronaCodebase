// CH3801.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 200;
int n, arr[MAX_N];
double ans1, ans2, ans3;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    for (int k = 0; k < 30; k++)
    {
        int last[2], c1 = 0, c2 = 0;
        last[0] = last[1] = 0;
        for (int i = 1; i <= n; i++)
            if ((arr[i] >> k) & 1)
            {
                ans1 += (1 << k) * 1.0 / n / n;
                ans2 += (1 << k) * 1.0 / n / n;
                ans3 += (1 << k) * 1.0 / n / n;
                ans1 += (1 << k) * 2.0 / n / n * c1;
                ans2 += (1 << k) * 2.0 / n / n * (i - 1);
                ans3 += (1 << k) * 2.0 / n / n * (i - 1 - last[0]);
                last[1] = i;
                c1++, swap(c1, c2);
            }
            else
            {
                ans1 += (1 << k) * 2.0 / n / n * c2;
                ans2 += (1 << k) * 2.0 / n / n * (last[1]);
                last[0] = i, c1++;
            }
    }
    printf("%.3lf %.3lf %.3lf", ans1, ans3, ans2);
    return 0;
}