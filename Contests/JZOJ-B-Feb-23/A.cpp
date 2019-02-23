// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 100220;
int n, seqA[MAX_N], seqB[MAX_N], tmp[MAX_N];
void merge_units(int *seq, int cur)
{
    int f1 = 1, f2 = cur, tot = 0;
    while (f1 < cur && f2 == cur)
        if (seq[f1] < seq[f2])
            tmp[++tot] = seq[f1], f1++;
        else
            tmp[++tot] = seq[f2], f2++;
    while (f1 < cur)
        tmp[++tot] = seq[f1], f1++;
    while (f2 == cur)
        tmp[++tot] = seq[f2], f2++;
    for (int i = 1; i <= cur; i++)
        seq[i] = tmp[i];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &seqA[i], &seqB[i]);
        merge_units(seqA, i), merge_units(seqB, i);
        int ans = 0;
        for (int j = 1; j <= i; j++)
            ans = max(seqA[j] + seqB[i - j + 1], ans);
        printf("%d\n", ans);
    }
    return 0;
}