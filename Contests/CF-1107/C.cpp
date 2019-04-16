// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5 + 2000;
int n, k, arr[MAX_N];
char str[MAX_N];
bool cmp(int a, int b)
{
    return a > b;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    scanf("%s", str + 1);
    char previousVal = str[1];
    long long previousKey = 1;
    for (int i = 1; i <= n; i++)
    {
        if (str[i] != previousVal)
            sort(arr + previousKey, arr + i, cmp), previousKey = i;
        previousVal = str[i];
    }
    sort(arr + previousKey, arr + n + 1, cmp);
    long long tim = 0, ans = 0;
    char lastkey = str[1];
    for (int i = 1; i <= n; i++)
    {
        if (str[i] != lastkey)
            tim = 0, lastkey = str[i];
        if (tim < k)
            tim++, ans += arr[i];
    }
    printf("%lld", ans);
    return 0;
}