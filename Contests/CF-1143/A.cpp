// A.cpp
#include <bits/stdc++.h>
using namespace std;
int seq[200100];
int main()
{
    int left = 0, right = 0, n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]), (seq[i] == 0) ? left++ : right++;
    int a = 0, b = 0;
    for (int i = 1; i <= n; i++)
    {
        (seq[i] == 0) ? a++ : b++;
        if (a == left || b == right)
            printf("%d", i), exit(0);
    }
    return 0;
}