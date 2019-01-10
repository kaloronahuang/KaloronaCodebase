// A.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
int main()
{
    scanf("%d", &n);
    if (n == 1 || n == 2)
        printf("1");
    else if (n == 3 || n == 0)
        printf("0");
    else
    {
        int res = n % 4;
        if(res == 0 || res == 3)
            printf("0");
        else
            printf("1");
    }
    return 0;
}