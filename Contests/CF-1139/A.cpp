// A.cpp
#include <bits/stdc++.h>
using namespace std;
char str[66000];
int main()
{
    int ans = 0, len;
    scanf("%d", &len), scanf("%s", str + 1);
    for (int i = 1; i <= len; i++)
        if (((str[i] - '0') & 1) == 0)
            ans += i;
    printf("%d", ans);
    return 0;
}