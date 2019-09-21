// random.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int seq[MAX_N], n, tmp[MAX_N], tmp_pos[MAX_N], pos[MAX_N], ans = 0x3f3f3f3f;

void mergeSort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    mergeSort(l, mid), mergeSort(mid + 1, r);
    int ptr1 = l, ptr2 = mid + 1, ptr = l;
    while (ptr1 <= mid && ptr2 <= r)
        if (seq[ptr1] < seq[ptr2])
        {
            tmp[ptr] = seq[ptr1], tmp_pos[ptr++] = pos[ptr1], ans = min(ans, max(abs(seq[ptr2] - seq[ptr1]), abs(pos[ptr1] - pos[ptr2]) + 1)), ptr1++;
            continue;
        }
        else
        {
            tmp[ptr] = seq[ptr2], tmp_pos[ptr++] = pos[ptr2], ans = min(ans, max(abs(seq[ptr2] - seq[ptr1]), abs(pos[ptr1] - pos[ptr2]) + 1)), ptr2++;
            continue;
        }
    while (ptr1 <= mid)
        tmp[ptr] = seq[ptr1], tmp_pos[ptr++] = pos[ptr1++];
    while (ptr2 <= r)
        tmp[ptr] = seq[ptr2], tmp_pos[ptr++] = pos[ptr2++];
    for (int i = l; i <= r; i++)
    {
        seq[i] = tmp[i], pos[i] = tmp_pos[i];
        if (i > l)
            ans = min(ans, max(abs(pos[i] - pos[i - 1]) + 1, abs(seq[i] - seq[i - 1])));
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), pos[i] = i;
    mergeSort(1, n), printf("%d", ans);
    return 0;
}