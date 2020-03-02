// CF1161C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 55;

int n, ai[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    int min_val = *min_element(ai + 1, ai + 1 + n), cnt = 0;
    for (int i = 1; i <= n; i++)
        if (ai[i] == min_val)
            cnt++;
    if (cnt <= (n >> 1))
        puts("Alice");
    else
        puts("Bob");
    return 0;
}