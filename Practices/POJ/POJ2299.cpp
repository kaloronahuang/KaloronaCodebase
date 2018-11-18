// POJ2299.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
const int maxn = 500200;
ll n, seq[maxn], ans, tmp[maxn];
void merge(int l, int mid, int r)
{
    int p1 = l, p2 = mid + 1, bias = l;
    while (p1 <= mid && p2 <= r)
        if (seq[p1] <= seq[p2])
            tmp[bias++] = seq[p1++];
        else
            tmp[bias++] = seq[p2++], ans += (mid - p1 + 1);
    while (p1 <= mid)
        tmp[bias++] = seq[p1++];
    while (p2 <= r)
        tmp[bias++] = seq[p2++];
    for (int i = l; i <= r; i++)
        seq[i] = tmp[i];
}

void mergeSort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid), mergeSort(mid + 1, r);
    merge(l, mid, r);
}

int main()
{
    for (scanf("%lld", &n); n != 0; scanf("%lld", &n))
    {
        for (int i = 1; i <= n; i++)
            scanf("%lld", &seq[i]);
        ans = 0;
        mergeSort(1, n);
        printf("%lld\n", ans);
    }
    return 0;
}