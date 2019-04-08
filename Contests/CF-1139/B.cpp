// B.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = (int)2e5 + 2000;
int n, arr[MAX_N], trial[MAX_N];
ll check()
{
    memset(trial, 0x3f, sizeof(trial));
    ll acc = 0;
    for (int i = n; i >= 1; i--)
    {
        if (trial[i + 1] == 0)
        {
            trial[i] = 0;
            continue;
        }
        trial[i] = min(trial[i + 1] - 1, arr[i]);
        acc += trial[i];
    }
    return acc;
}
int main()
{
    ll l = 0, r = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), r += arr[i];
    printf("%lld", check());
    return 0;
}