// AtCoder Beginner Contest 115 - D.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;
int phi(int i)
{
    return (1 << (i + 1)) - 1;
}
int len(int i)
{
    return (1 << (i + 2)) - 2;
}
int anss[7] = {0, 0, 0, 1, 2, 3, 3};
int f(int x, int n)
{
    if (n == 1)
        return anss[x];
    if (x > len(n) / 2)
        return phi(n) - f(len(n) - x, n);
    else
        return f(x - 1, n - 1);
}

int main()
{
    int N, X;
    scanf("%d%d", &N, &X);
    cout << f(X + 1, N);
    return 0;
}