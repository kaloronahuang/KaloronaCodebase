// CH0503.cpp
#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
const int maxn = 400000;
ll seq[maxn], tmp[maxn], n, ans = 0;

void merge(int l, int mid, int r)
{
    ll p1 = l, p2 = mid + 1, bias = l;
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
    if (l >= r)
        return;
    ll mid = (l + r) >> 1;
    mergeSort(l, mid), mergeSort(mid + 1, r);
    merge(l, mid, r);
}

int main()
{
    while (scanf("%lld", &n) != EOF)
    {
        if (n == 1)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == y)
                printf("TAK\n");
            else
                printf("NIE\n");
            continue;
        }
        ll ans1, ans2, num;
        ans = 0, seq[1] = 0;
        for (int i = 2; i <= n * n; i++)
        {
            scanf("%lld", &num);
            if (num == 0)
                i--, seq[1] = -1;
            else
                seq[i] = num;
        }
        if (seq[1] == 0)
            scanf("%d", &num);
        mergeSort(2, n * n);
        ans1 = ans, ans = seq[1] = 0;
        for (int i = 2; i <= n * n; i++)
        {
            scanf("%lld", &num);
            if (num == 0)
                i--, seq[1] = -1;
            else
                seq[i] = num;
        }
        if (seq[1] == 0)
            scanf("%d", &num);
        mergeSort(2, n * n);
        ans2 = ans;
        if ((ans1 & 1) == (ans2 & 1))
            printf("TAK\n");
        else
            printf("NIE\n");
    }
    return 0;
}