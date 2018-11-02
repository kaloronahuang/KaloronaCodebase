// P1183.cpp
#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 200;
int n;
double xi[maxn];
double yi[maxn];

double getDist(int a, int b)
{
    return sqrt(pow(xi[a] - xi[b], 2) + pow(yi[a] - yi[b], 2));
}

double getSize(int a, int b, int c)
{
    double s1 = getDist(a, b);
    double s2 = getDist(b, c);
    double s3 = getDist(c, a);
    double p = (s1 + s2 + s3) / 2;
    return sqrt(p * (p - s1) * (p - s2) * (p - s3));
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> xi[i] >> yi[i];
    double size = 0;
    xi[n + 1] = xi[1];
    yi[n + 1] = yi[1];
    for (int i = 1; i <= n; i++)
        size += (xi[i] * yi[i + 1] - xi[i + 1] * yi[i]) / 2;
    cout << (int)size;
    return 0;
}