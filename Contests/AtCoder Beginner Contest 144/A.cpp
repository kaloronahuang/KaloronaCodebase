// A.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", (a < 10 && b < 10) ? a * b : -1);
    return 0;
}