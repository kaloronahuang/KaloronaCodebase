// CH0601.cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
const int maxn = 5000020;
using namespace std;
int pre[maxn], seq[maxn], tmp[maxn], n, m, k;
long long T;

long long doubleTimes(long long x)
{
    return x * x;
}

bool checkHash(int l, int r, int nr)
{
    if (l == r)
        seq[l] = pre[l];
    copy(pre + r + 1, pre + nr + 1, seq + r + 1);
    long long sum = 0;
    sort(seq + r + 1, seq + nr + 1);
    merge(seq + l, seq + r + 1, seq + r + 1, seq + nr + 1, tmp + l);
    int p1 = l, p2 = nr, pr = 0;
    while (p1 < p2 && pr < m && sum <= T)
        sum += doubleTimes(tmp[p1++] - tmp[p2--]), pr++;
    if (sum <= T)
        copy(tmp + l, tmp + nr + 1, seq + l);
    return (sum <= T);
}

int main()
{
    scanf("%d", &k);
    while (k--)
    {
        scanf("%d%d%lld", &n, &m, &T);
        for (int i = 1; i <= n; i++)
            scanf("%d", &pre[i]);
        int segs = 0;
        int p = 1, R;
        for (int L = 1; L <= n; L = R + 1)
        {
            p = 1, R = L;
            for (int i = 1; i <= n; i++)
                seq[i] = pre[i];
            while (p != 0 && R <= n)
                if (checkHash(L, R, min(n, R + p)))
                    R += p, p <<= 1;
                else
                    p >>= 1;
            segs++;
        }
        printf("%d\n", segs);
    }
    return 0;
}