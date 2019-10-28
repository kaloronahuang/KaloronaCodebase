// D.cpp
#include <bits/stdc++.h>
typedef double ld;

using namespace std;

const ld Pi = acos(-1.0);

ld a, b, V;

int main()
{
    cin >> a >> b >> V;
    if (V < a * a * b / 2)
    {
        ld ops = (V / (a * b)) * 2;
        printf("%.9lf", atan(b / ops) * 180.0 / Pi);
    }
    else
    {
        ld x = 2.0 * (ld(b) - (ld(V) / ld(a * a)));
        printf("%.9lf", atan(x / a) * 180.0 / Pi);
    }
    return 0;
}