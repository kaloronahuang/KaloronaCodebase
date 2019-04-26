// B.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 2000;
int n;
char str[MAX_N];

int main()
{
    scanf("%d%s", &n, str + 1);
    int cnt = 0, b = 0;
    for (int i = 1; i <= n - 10; i++)
        if (str[i] == '8')
            cnt++;
        else
            b++;
    if (cnt <= b)
        printf("NO");
    else
        printf("YES");
    return 0;
}