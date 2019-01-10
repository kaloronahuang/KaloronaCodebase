// C.cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, x, y, arr[110], num;
int main()
{
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), num += (arr[i] > x) ? 0 : 1;
    if (x > y)
        printf("%d", n);
    else
        printf("%d", (num + 1) >> 1);
    return 0;
}