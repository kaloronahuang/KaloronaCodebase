// CF1063A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n;
char str[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    sort(str + 1, str + 1 + n);
    printf("%s\n", str + 1);
    return 0;
}