// A.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    if (a == b)
        printf("%d02 %d03", a, b); // cout << a << "02 " << b << "03";
    else if (b - a == 1)
        printf("%d99 %d00", a, b);
    else if (a == 9 && b == 1)
        printf("99 100");
    else
        puts("-1");
    return 0;
}