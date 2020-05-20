// CF1354C2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

const double pi = acos(-1.0);

int T, n;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        printf("%.10lf\n", cos(pi / (4 * n)) / sin(pi / (2 * n)));
    }
    return 0;
}