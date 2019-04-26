// A.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3e5 + 2000;

int len, highest;
char str[MAX_N];

int main()
{
    scanf("%d%s", &len, str + 1);
    for (int i = 1; i <= len; i++)
    {
        if (str[i] < str[highest])
        {
            printf("YES\n%d %d", highest, i);
            return 0;
        }
        if (str[i] > str[highest])
            highest = i;
    }
    printf("NO");
    return 0;
}