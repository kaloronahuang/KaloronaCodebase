// card.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 100200;
int arr[MAX_N], n, tmp[MAX_N], seq[MAX_N];
int tmp_ans;
void mergeA(int l, int mid, int r)
{
    int pl = l, pr = mid + 1, cur = l;
    while (pl <= mid && pr <= r)
        if (seq[pl] <= seq[pr])
            tmp[cur++] = seq[pl++];
        else
            tmp_ans += mid - pl + 1, tmp[cur++] = seq[pr++];
    while (pl <= mid)
        tmp[cur++] = seq[pl++];
    while (pr <= r)
        tmp[cur++] = seq[pr++];
    for (int i = l; i <= r; i++)
        seq[i] = tmp[i];
}
void mergeSortA(int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    mergeSortA(l, mid), mergeSortA(mid + 1, r);
    mergeA(l, mid, r);
}
void mergeB(int l, int mid, int r)
{
    int pl = l, pr = mid + 1, cur = l;
    while (pl <= mid && pr <= r)
        if (seq[pl] >= seq[pr])
            tmp[cur++] = seq[pl++];
        else
            tmp_ans += pr - mid, tmp[cur++] = seq[pr++];
    while (pl <= mid)
        tmp[cur++] = seq[pl++];
    while (pr <= r)
        tmp[cur++] = seq[pr++];
    for (int i = l; i <= r; i++)
        seq[i] = tmp[i];
}
void mergeSortB(int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    mergeSortB(l, mid), mergeSortB(mid + 1, r);
    mergeB(l, mid, r);
}
int main()
{
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    int ans = 2e9;
    for (int i = 0; i <= n; i++)
    {
        copy(arr + 1, arr + n + 1, seq + 1);
        mergeSortA(1, i);
        mergeSortB(i + 1, n);
        ans = min(ans, tmp_ans);
        tmp_ans = 0;
    }
    printf("%d", ans);
    return 0;
}