// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
int si[MAX_N], di[MAX_N], n, t;
short aff[11000000];
int main()
{
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &si[i], &di[i]);
        for (int j = si[i]; j < 11000000; j += di[i])
            aff[j] = i;
    }
    for (int i = t; i < 11000000; i++)
        if (aff[i] != 0)
            printf("%d", aff[i]), exit(0);
    return 0;
}