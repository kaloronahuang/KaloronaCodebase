// P1415.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 550;
int f[MAX_N], dp[MAX_N], numarr[MAX_N];
string str;
bool smaller(int i, int j, int a, int b)
{
    int cur1 = i, cur2 = a;
    for (; j - cur1 > b - cur2; cur1++)
        if (numarr[cur1])
            return false;
    for (; j - cur1 < b - cur2; cur2++)
        if (numarr[cur2])
            return true;
    while (cur1 <= j)
    {
        if (numarr[cur1] < numarr[cur2])
            return true;
        else if (numarr[cur1] > numarr[cur2])
            return false;
        cur1++, cur2++;
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> str;
    int siz = str.length();
    str = " " + str;
    for (int i = 1; i <= siz; i++)
        numarr[i] = str[i] - '0';
    for (int i = 1; i <= siz; i++)
    {
        f[i] = 1;
        for (int j = i; j >= 1; j--)
            if (smaller(f[j - 1], j - 1, j, i))
            {
                f[i] = max(f[i], j);
                break;
            }
    }
    dp[f[siz]] = siz;
    int cnt = 0;
    for (int i = f[siz] - 1; i >= 1 && !numarr[i]; i--)
        cnt++, dp[i] = siz;
    for (int i = f[siz] - cnt - 1; i >= 1; i--)
    {
        dp[i] = i;
        for (int j = f[siz] - 1; j >= i; j--)
            if (smaller(i, j, j + 1, dp[j + 1]))
            {
                dp[i] = max(dp[i], j);
                break;
            }
    }
    bool flag = true;
    for (int pos = 1; pos <= siz;)
    {
        if (flag)
            flag = false;
        else
            printf(",");
        for (int i = pos; i <= dp[pos]; i++)
            printf("%d", numarr[i]);
        pos = dp[pos] + 1;
    }
    return 0;
}