// E.cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1000200;
int arr[maxn];
int n;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    int min_val = arr[1];
    int ans = 0;
    for (int i = 2; i <= n; i++)
        ans = max(arr[i] - min_val, ans), min_val = min(min_val, arr[i]);
    cout << ans;
    return 0;
}