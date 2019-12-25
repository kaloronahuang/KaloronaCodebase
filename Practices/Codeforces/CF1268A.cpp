// CF1268A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, k;
char str[MAX_N];
int digits[MAX_N];

int main()
{
    scanf("%d%d%s", &n, &k, str + 1);
    for (int i = 1; i <= n; i++)
        digits[i] = str[i] - '0';
    // compare the nxt substr;
    bool flag = false;
    for (int i = k + 1; i <= n; i++)
        if (digits[(i - 1) % k + 1] > digits[i])
            break;
        else if (digits[(i - 1) % k + 1] < digits[i])
        {
            flag = true;
            break;
        }
    if (flag)
        digits[k]++;
    for (int i = k; i >= 1; i--)
        if (digits[i] >= 10)
            digits[i] -= 10, digits[i - 1]++;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("%d", digits[(i - 1) % k + 1]);
    return 0;
}