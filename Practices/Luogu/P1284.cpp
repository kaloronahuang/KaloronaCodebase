// P1284.cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
bool dp[800][800];
int n, li[400], c;
bool isTriangle(int a, int b, int c) { return (a + b) > c && (b + c) > 1 && (c + a) > b; }
double getSize(double a, double b, double c)
{
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &li[i]), c += li[i];
    int half = c / 2;
    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = half; j >= 0; j--)
            for (int k = j; k >= 0; k--)
                if ((j >= li[i] && dp[j - li[i]][k]) || (k >= li[i] && dp[j][k - li[i]]))
                    dp[j][k] = true;
    double maxs = -1;
    for (int i = half; i >= 0; i--)
        for (int j = i; j >= 0; j--)
            if (dp[i][j] && isTriangle(i, j, c - i - j))
                maxs = max(maxs, getSize(i, j, c - i - j));
    if (maxs == -1)
        printf("%d", -1);
    else
        printf("%d", (int)(maxs * 100));
    return 0;
}