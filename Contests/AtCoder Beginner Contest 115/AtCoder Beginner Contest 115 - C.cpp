// AtCoder Beginner Contest 115 - C.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
const int maxn = 100200;
using namespace std;
int n, arr[maxn], K;
int main()
{
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    sort(arr + 1, arr + 1 + n);
    int min_val = 1e9;
    for (int i = K; i <= n; i++)
        min_val = min(min_val, arr[i] - arr[i - K + 1]);
    printf("%d", min_val);
    return 0;
}