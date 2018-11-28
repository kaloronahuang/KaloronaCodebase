// POJ3974.cpp
#include <iostream>
#include <cstdio>
#define ll unsigned long long
using namespace std;
string str;
const int maxn = 1000000 + 1000;
ll bitNum = 131, power[maxn], hashtable[maxn], rev[maxn];

ll getHash(int l, int r)
{
    return hashtable[r] - hashtable[l - 1] * power[r - l + 1];
}

ll getRevHash(int l, int r)
{
    return rev[l] - rev[r + 1] * power[r - l + 1];
}

int main()
{
    int cnt = 1;
    power[0] = 1;
    for (int i = 1; i < maxn; i++)
        power[i] = power[i - 1] * bitNum;
    while (cin >> str)
    {
        if (str == "END")
            break;
        // done with the process;
        int siz = str.length(), ans = 0;
        str = " " + str;
        hashtable[0] = 0;
        for (int i = 1; i <= siz; i++)
            hashtable[i] = hashtable[i - 1] * bitNum + (str[i] - '0' + 1);
        rev[siz + 1] = 0;
        for (int i = siz; i > 0; i--)
            rev[i] = rev[i + 1] * bitNum + (str[i] - '0' + 1);
        // do with binary;
        for (int pos = 1; pos <= siz; pos++)
        {
            int l = 1, r = min(siz - pos, pos - 1);
            while (l < r)
            {
                int mid = (l + r + 1) >> 1;
                if (getHash(pos - mid, pos - 1) == getRevHash(pos + 1, pos + mid))
                    l = mid;
                else
                    r = mid - 1;
            }
            ans = max(ans, 2 * l + 1);
            l = 1, r = min(siz - pos + 1, pos - 1);
            while (l < r)
            {
                int mid = (l + r + 1) >> 1;
                if (getHash(pos - mid, pos - 1) == getRevHash(pos, pos + mid - 1))
                    l = mid;
                else
                    r = mid - 1;
            }
            ans = max(ans, 2 * l);
        }
        printf("Case %d: %d\n", cnt++, ans);
    }
    return 0;
}