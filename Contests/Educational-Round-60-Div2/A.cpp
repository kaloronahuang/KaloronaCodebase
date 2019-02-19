// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 200;
int arr[MAX_N], n, mx = -2e9;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), mx = max(arr[i], mx);
    int siz = 0, acc = 0;
    for (int i = 1; i <= n; i++)
        if (arr[i] == mx)
            acc++;
        else
            siz = max(acc, siz), acc = 0;
    siz = max(acc, siz);
    printf("%d", siz);
    return 0;
}