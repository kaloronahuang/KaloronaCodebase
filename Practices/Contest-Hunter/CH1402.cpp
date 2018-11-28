// CH1402.cpp
#include <iostream>
#include <algorithm>
#define ull long long
using namespace std;

const int maxn = 300000 + 1000;
string str = "";
int idxs[maxn], siz;
ull hashtable[maxn], power[maxn], bitNum = 133;

bool cmp(int a, int b)
{
    int range = min(str.length() - a + 1, str.length() - b + 1);
    int l = 0, r = range, pl = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (hashtable[a + mid - 1] - hashtable[a - 1] * power[mid] == hashtable[b + mid - 1] - hashtable[b - 1] * power[mid])
            l = mid + 1, pl = mid;
        else
            r = mid - 1;
    }
    return str[a + pl] < str[b + pl];
}

int getLen(int a, int b)
{
    int range = min(str.length() - a + 1, str.length() - b + 1);
    int l = 0, r = range, pl = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (hashtable[a + mid - 1] - hashtable[a - 1] * power[mid] == hashtable[b + mid - 1] - hashtable[b - 1] * power[mid])
            l = mid + 1, pl = mid;
        else
            r = mid - 1;
    }
    return pl;
}

int main()
{
    cin >> str;
    siz = str.length();
    str = ' ' + str, power[0] = 1;
    for (int i = 1; i <= siz; i++)
        hashtable[i] = hashtable[i - 1] * bitNum + str[i] - 'a' + 1,
        power[i] = power[i - 1] * bitNum,
        idxs[i] = i;
    sort(idxs + 1, idxs + siz + 1, cmp);
    for (int i = 1; i <= siz; i++)
        printf("%d ", idxs[i] - 1);
    printf("\n0 ");
    for (int i = 2; i <= siz; i++)
        printf("%d ", getLen(idxs[i], idxs[i - 1]));
    return 0;
}