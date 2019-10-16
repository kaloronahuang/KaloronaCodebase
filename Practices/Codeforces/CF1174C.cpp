// CF1174C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, ncnt, color[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        if (color[i] == 0)
        {
            ++ncnt;
            for (int j = i; j <= n; j += i)
                color[j] = ncnt;
        }
    for (int i = 2; i <= n; i++)
        printf("%d ", color[i]);
    return 0;
}