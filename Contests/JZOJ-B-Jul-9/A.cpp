// A.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

ull arr[10], t;

int main()
{
    scanf("%llu", &t);
    while (t--)
    {
        ull ans = 0;
        for (int i = 1; i <= 8; i++)
            scanf("%llu", &arr[i]), ans += (((ull)(1)) << arr[i]);
        scanf("%llu", &arr[9]), ans += arr[9];
        if (ans == 0)
            printf("18446744073709551616\n");
        else
            printf("%llu\n", ans);
    }
    return 0;
}