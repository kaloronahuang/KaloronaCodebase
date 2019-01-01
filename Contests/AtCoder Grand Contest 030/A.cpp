// A.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
ll A, B, C;
int main()
{
    scanf("%lld%lld%lld", &A, &B, &C);
    if (B >= C || B + A >= C - 1)
        printf("%lld", B + C);
    else
        printf("%lld", min(C, A + B + 1) + B);
    return 0;
}