// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e6 + 200;

int n, k, tim[(1 << 21)];
char str[MAX_N];

int main()
{
    scanf("%s", str + 1), n = strlen(str + 1);
    scanf("%d", &k);
    int ans = 0;
    for (int i = 1, stat = 0; i <= n; i++)
    {
        int bit = 0;
        if (str[i] == 'A')
            bit = 0;
        else if (str[i] == 'G')
            bit = 1;
        else if (str[i] == 'C')
            bit = 2;
        else
            bit = 3;
        stat = (stat >> 2) | (bit << ((k - 1) * 2));
        if (i >= k)
            ans = max(ans, ++tim[stat]);
    }
    printf("%d", ans);
    return 0;
}