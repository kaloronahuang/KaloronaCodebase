// P3809.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int len, sa[MAX_N], rk[MAX_N], height[MAX_N], secondKeywords[MAX_N];
int wordset = 75, bucket[MAX_N];
char str[MAX_N];

void bucketSort()
{
    for (int i = 0; i <= wordset; i++)
        bucket[i] = 0;
    for (int i = 1; i <= len; i++)
        bucket[rk[i]]++;
    for (int i = 1; i <= wordset; i++)
        bucket[i] += bucket[i - 1];
    for (int i = len; i >= 1; i--)
        sa[bucket[rk[secondKeywords[i]]]--] = secondKeywords[i];
}

void suffixSort()
{
    wordset = 75;
    for (int i = 1; i <= len; i++)
        rk[i] = str[i] - '0' + 1, secondKeywords[i] = i;
    bucketSort();
    for (int step = 1, p = 0; p < len; wordset = p, step <<= 1)
    {
        p = 0;
        // set the rest positions;
        for (int i = 1; i <= step; i++)
            secondKeywords[++p] = len - step + i;
        // make the first bit;
        for (int i = 1; i <= len; i++)
            if (sa[i] > step)
                secondKeywords[++p] = sa[i] - step;
        bucketSort();
        swap(secondKeywords, rk);
        rk[sa[1]] = p = 1;
        for (int i = 2; i <= len; i++)
            rk[sa[i]] = (secondKeywords[sa[i - 1]] == secondKeywords[sa[i]] && secondKeywords[sa[i - 1] + step] == secondKeywords[sa[i] + step]) ? p : ++p;
    }
}

int main()
{
    scanf("%s", str + 1);
    len = strlen(str + 1);
    suffixSort();
    for (int i = 1; i <= len; i++)
        printf("%d ", sa[i]);
    return 0;
} // P3809.cpp