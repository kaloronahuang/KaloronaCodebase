// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 50200, NUM_DOMAIN = 6e5;
pair<int, int> prs[MAX_N];
int arr[MAX_N], n, maxl[MAX_N], maxr[MAX_N], minl[MAX_N], minr[MAX_N], bucket[2 * NUM_DOMAIN + 1];
long long answer = 0;
void dq(int l, int r)
{
    if (l == r)
    {
        answer++;
        return;
    }
    int mid = (l + r) >> 1;
    // preprocessing;
    minl[mid] = arr[mid], maxl[mid] = arr[mid];
    maxr[mid + 1] = arr[mid + 1], minr[mid + 1] = arr[mid + 1];
    for (int i = mid - 1; i >= l; i--)
        minl[i] = min(minl[i + 1], arr[i]), maxl[i] = max(maxl[i + 1], arr[i]);
    for (int i = mid + 2; i <= r; i++)
        maxr[i] = max(maxr[i - 1], arr[i]), minr[i] = min(minr[i - 1], arr[i]);
    // make judges;
    // at the left:
    for (int i = mid; i >= l; i--)
    {
        int j = i + (maxl[i] - minl[i]);
        if (j > mid && j <= r && minr[j] > minl[i] && maxr[j] < maxl[i])
            answer++;
    }
    // at the right;
    for (int i = mid + 1; i <= r; i++)
    {
        int j = i - (maxr[i] - minr[i]);
        if (j <= mid && j >= l && minl[j] > minr[i] && maxl[j] < maxr[i])
            answer++;
    }
    // in the middle;
    // min|max:
    int ptr1 = mid + 1, ptr2 = mid;
    for (int i = mid; i >= l; i--)
    {
        while (minr[ptr2 + 1] > minl[i] && ptr2 < r)
            ptr2++, bucket[maxr[ptr2] - ptr2 + NUM_DOMAIN]++;
        while (maxl[i] > maxr[ptr1])
        {
            bucket[maxr[ptr1] - ptr1 + NUM_DOMAIN]--, ptr1++;
            if (ptr1 > r)
                break;
        }
        if (ptr1 > r)
            break;
        if (ptr1 <= ptr2)
            answer += bucket[minl[i] - i + NUM_DOMAIN];
    }
    for (int i = mid; i >= l; i--)
        bucket[minl[i] - i + NUM_DOMAIN] = 0;
    for (int i = mid + 1; i <= r; i++)
        bucket[maxr[i] - i + NUM_DOMAIN] = 0;
    // max|min:
    ptr1 = mid,
    ptr2 = mid + 1;
    for (int i = mid + 1; i <= r; i++)
    {
        while (minl[ptr2 - 1] > minr[i] && ptr2 > l)
            ptr2--, bucket[maxl[ptr2] + ptr2 + NUM_DOMAIN]++;
        while (maxr[i] > maxl[ptr1])
        {
            bucket[maxl[ptr1] + ptr1 + NUM_DOMAIN]--, ptr1--;
            if (ptr1 < l)
                break;
        }
        if (ptr1 < l)
            break;
        if (ptr2 <= ptr1)
            answer += bucket[minr[i] + i + NUM_DOMAIN];
    }
    for (int i = mid + 1; i <= r; i++)
        bucket[minr[i] + i + NUM_DOMAIN] = 0;
    for (int i = mid; i >= l; i--)
        bucket[maxl[i] + i + NUM_DOMAIN] = 0;
    dq(l, mid), dq(mid + 1, r);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &prs[i].first, &prs[i].second);
    for (int i = 1; i <= n; i++)
        arr[prs[i].first] = prs[i].second;
    dq(1, n);
    printf("%lld", answer);
    return 0;
}