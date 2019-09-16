// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;
const double eps = 1e-9;

int n;
char str[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    long double tot1 = 0, tot2 = 0;
    for (int i = 1; i <= n; i++)
        if (str[i] != '?')
            ((i > (n >> 1)) ? tot2 : tot1) += (str[i] - '0');
        else
            ((i > (n >> 1)) ? tot2 : tot1) += 4.5;
    if (fabs(tot1 - tot2) < eps)
        printf("Bicarp");
    else
        printf("Monocarp");
    return 0;
}