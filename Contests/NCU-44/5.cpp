// 5.cpp
#include <bits/stdc++.h>

using namespace std;

int S, Q, x;

int main()
{
    scanf("%d%d", &S, &Q);
    while (Q--)
    {
        scanf("%d", &x), printf("%d\n", (S - (x % S)) % S);
    }
    return 0;
}