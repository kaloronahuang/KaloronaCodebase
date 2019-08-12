// P2408.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, wordset = 75, sa[MAX_N], rk[MAX_N], sc[MAX_N], bucket[MAX_N], height[MAX_N];
char str[MAX_N];

void bucketSort()
{
    for (int i = 0; i <= wordset; i++)
        bucket[i] = 0;
    for (int i = 1; i <= n; i++)
        bucket[rk[i]]++;
    for (int i = 1; i <= wordset; i++)
        bucket[i] += bucket[i - 1];
    for (int i = n; i >= 1; i--)
        sa[bucket[rk[sc[i]]]--] = sc[i];
}

void suffixSort()
{
    for (int i = 1; i <= n; i++)
        rk[i] = str[i] - '0' + 1, sc[i] = i;
    bucketSort();
    for (int step = 1, p = 0; p < n; wordset = p, step <<= 1)
    {
        p = 0;
        for (int i = n - step + 1; i <= n; i++)
            sc[++p] = i;
        for (int i = 1; i <= n; i++)
            if (sa[i] > step)
                sc[++p] = sa[i] - step;
        bucketSort();
        swap(rk, sc);
        rk[sa[1]] = p = 1;
        for (int i = 2; i <= n; i++)
            rk[sa[i]] = (sc[sa[i]] == sc[sa[i - 1]] && sc[sa[i] + step] == sc[sa[i - 1] + step]) ? p : ++p;
    }
}

void getHeight()
{
    int k = 0;
    for (int i = 1; i <= n; i++)
    {
        if (k != 0)
            k--;
        int j = sa[rk[i] - 1];
        while (str[i + k] == str[j + k])
            k++;
        height[rk[i]] = k;
    }
}

int main()
{
    scanf("%d%s", &n, str + 1);
    suffixSort(), getHeight();
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += n - sa[i] + 1 - height[i];
    printf("%lld", ans);
    return 0;
} // P2408.cpp