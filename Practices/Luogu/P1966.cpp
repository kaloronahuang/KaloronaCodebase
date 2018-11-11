// P1966.cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000200;
const int mod = 99999997;
#define ll long long
struct element
{
    int val, idx;
    bool operator<(const element &ele) const
    {
        return val < ele.val;
    }
} a[maxn], b[maxn];
int mapping[maxn], tmp[maxn], n;
int ans = 0;

void merge(int l, int mid, int r)
{
    int sa = l;
    int p = mid + 1;
    int bias = l;
    while (sa <= mid && p <= r)
        if (mapping[sa] < mapping[p])
            tmp[bias++] = mapping[sa++];
        else
            tmp[bias++] = mapping[p++], ans += (mid - sa + 1), ans %= mod;
    while (sa <= mid)
        tmp[bias++] = mapping[sa++];
    while (p <= r)
        tmp[bias++] = mapping[p++];
    for (int i = l; i <= r; i++)
        mapping[i] = tmp[i];
}

void mergeSort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    merge(l, mid, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].val), a[i].idx = i;
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i].val), b[i].idx = i;
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
        mapping[a[i].idx] = b[i].idx;
    mergeSort(1, n);
    cout << ans;
    return 0;
}