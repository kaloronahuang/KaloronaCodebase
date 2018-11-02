// P1908.cpp
// Merge sort;
#include <iostream>
#include <cstdio>
using namespace std;
#define INF 210000000
long long seq[500010];
long long n;
long long ans = 0;

void init()
{
    cin >> n;
    for (long long i = 0; i < n; i++)
        cin >> seq[i];
}

void MergeSort(long long l, long long r)
{
    if (l >= r)
        return;
    long long mid = (l + r) / 2;
    MergeSort(l, mid);
    MergeSort(mid + 1, r);
    // Arraies;
    long long seqa[mid - l + 2], seqb[r - mid + 1];
    for (long long i = 0; i < mid - l + 1; i++)
        seqa[i] = seq[l + i];
    seqa[mid - l + 1] = INF;
    for (long long i = 0; i < r - mid; i++)
        seqb[i] = seq[mid + 1 + i];
    seqb[r - mid] = INF;
    // Parameters;
    long long posa = 0;
    long long posb = 0;
    for (long lon  ag currentPos = l; currentPos <= r; currentPos++)
        if (seqa[posa] <= seqb[posb])
            seq[currentPos++] = seqa[posa++];
        else
        {
            ans += mid - l + 1 - posa;
            seq[currentPos++] = seqb[posb++];
        }
}

void print()
{
    for (long long j = 0; j < n; j++)
        cout << seq[j] << " ";
}

int main()
{
    freopen("test.in", "r", stdin);
    init();
    MergeSort(0, n - 1);
    cout << ans;
    return 0;
}