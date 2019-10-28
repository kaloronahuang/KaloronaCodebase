// B.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int prod;
    scanf("%d", &prod);
    for (int i = 9; i >= 1; i--)
        if (prod % i == 0 && (prod / i) <= 9)
            puts("Yes"), exit(0);
    puts("No");
    return 0;
}