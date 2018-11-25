#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 110;
#define ll long long
ll arr[maxn], n;

int main()
{
    scanf("%lld", &n);
    double avg = 0, eps = 1e9;
    int idx = 1e9;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &arr[i]), avg += arr[i];
    avg /= n;
    for (int i = 1; i <= n; i++)
        if (abs(arr[i] - avg) < eps)
            idx = i, eps = abs(arr[i] - avg);
    printf("%d", idx - 1);
    return 0;
}