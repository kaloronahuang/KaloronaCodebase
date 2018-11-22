// T55880.cpp
#include <iostream>
#include <cstdio>
#include <string>
#define ll long long
using namespace std;
int T, nt;
ll hashcode(string str)
{
    ll res = 0;
    ll siz = str.size();
    for (int i = 0; i < siz; i++)
        res += str[i];
    res += siz / 2;
    return res;
}
int main()
{
    scanf("%d", &T), nt = T;
    while (T--)
    {
        int cnt = 0, n, hashval;
        scanf("%d%d", &n, &hashval);
        string curt;
        for (int i = 1; i <= n; i++)
        {
            cin >> curt;
            if (hashcode(curt) == hashval)
            {
                cnt = i;
                break;
            }
        }
        cnt = (cnt == 0) ? -1 : cnt;
        printf("Case %d:\n%d\n", nt - T, cnt);
    }
    return 0;
}