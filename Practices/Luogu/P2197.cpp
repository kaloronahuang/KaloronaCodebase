// P2197.cpp
#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, ans = 0, num;
        scanf("%d", &n);
        while (n--)
            scanf("%d", &num), ans ^= num;
        if (ans == 0)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}