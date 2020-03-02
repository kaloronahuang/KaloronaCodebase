// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, task, ai[MAX_N];
double sum, res;

int main()
{
    scanf("%d%d%d", &n, &m, &task);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), sum += ai[i];
    res = sum + m;
    for (int i = 1; i <= n; i++)
        printf("%.10lf ", 1.0 * res * double(ai[i]) / sum);
    return 0;
}