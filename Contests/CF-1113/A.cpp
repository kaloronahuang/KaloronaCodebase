// A.cpp
#include <bits/stdc++.h>
using namespace std;
int n, v;
int main()
{
    scanf("%d%d", &n, &v);
    int tank = 0, ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (tank - (n - i) < 0)
        {
            if (n - i < v)
            {
                ans += i * ((n - i) - tank);
                tank = (n - i);
            }
            else
            {
                ans += i * (v - tank);
                tank = v;
            }
        }
        tank--;
    }
    printf("%d", ans);
    return 0;
}