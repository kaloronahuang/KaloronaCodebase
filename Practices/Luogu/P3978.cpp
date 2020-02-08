// P3978.cpp
#include <bits/stdc++.h>

using namespace std;

int n;

int main()
{
    scanf("%d", &n);
    printf("%.10lf\n", 1.0 * n * (n + 1) / double(2.0 * (2.0 * n - 1)));
    return 0;
}