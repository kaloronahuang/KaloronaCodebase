// A.cpp
#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_N = 50100, bitnum = 123;

char strA[MAX_N], strB[MAX_N];
int lenA, lenB;
ull hashA[MAX_N], hashB[MAX_N], bitnum_pow[MAX_N];

ull getHash(ull *arr, int l, int r) { return (l > r) ? 0x3f3f3f3f3f3f3f3f : arr[r] - arr[l - 1] * bitnum_pow[r - l + 1]; }

bool check(int len)
{
    for (int lft = 1; lft + len - 1 <= lenB; lft++)
    {
        int l = lft + 1, r = lft + len - 1, k = -1;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (getHash(hashA, 1, mid - lft) == getHash(hashB, lft, mid - 1))
                l = mid + 1, k = mid;
            else
                r = mid - 1;
        }
        if (k != -1 && strA[k - lft + 1] != strB[k] && getHash(hashA, k - lft + 2, len) == getHash(hashB, k + 1, lft + len - 1))
            return true;
    }
    return false;
}

bool check_sub(int len)
{
    for (int lft = 1; lft + len - 1 <= lenB; lft++)
        if (getHash(hashB, lft, lft + len - 1) == getHash(hashA, 1, len))
            return true;
    return false;
}

int main()
{
    scanf("%s", strA + 1), scanf("%s", strB + 1);
    lenA = strlen(strA + 1), lenB = strlen(strB + 1);
    for (int i = 1; i <= lenA; i++)
        hashA[i] = hashA[i - 1] * bitnum + strA[i] - 'a';
    for (int i = 1; i <= lenB; i++)
        hashB[i] = hashB[i - 1] * bitnum + strB[i] - 'a';
    bitnum_pow[0] = 1;
    for (int i = 1; i <= max(lenA, lenB); i++)
        bitnum_pow[i] = bitnum_pow[i - 1] * bitnum;

    // begin to binary search;
    int l = 2, r = min(lenA, lenB), ans = 2, substr = 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    //printf("%llu %llu\n", getHash(hashA, 1, 20002), getHash(hashB, 1, 20002));
    // begin to search the least prefix;
    l = 1, r = min(lenA, lenB) + 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check_sub(mid))
            l = mid + 1, substr = mid;
        else
            r = mid - 1;
    }
    printf("%d", max(ans, substr));
    return 0;
}