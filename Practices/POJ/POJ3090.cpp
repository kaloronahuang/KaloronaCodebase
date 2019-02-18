// POJ3090.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1100;
int phi[MAX_N], T, n;
int main()
{
    scanf("%d", &T);
    for (int i = 2; i < MAX_N; i++)
        phi[i] = i;
    for (int i = 2; i < MAX_N; i++)
        if (phi[i] == i)
            for (int j = i; j < MAX_N; j += i)
                phi[j] = phi[j] / i * (i - 1);
    int idx = 1;
    while (T--)
    {
        scanf("%d", &n);
        int ans = 3;
        for (int i = 2; i <= n; i++)
            ans += (phi[i] << 1);
        printf("%d %d %d\n", idx, n, ans);
        idx++;
    }
    return 0;
}