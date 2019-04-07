// B.cpp
#include <bits/stdc++.h>
using namespace std;
int ans, num, number, numarr[20], digit;
int main()
{
    scanf("%d", &num), number = num;
    int ans = 1;
    while (num)
        numarr[++digit] = num % 10, num /= 10, ans *= numarr[digit];
    if (digit == 1)
        printf("%d", numarr[1]), exit(0);
    for (int i = digit; i >= 1; i--)
    {
        int acc = 1;
        for (int j = digit; j >= i + 1; j--)
            acc *= numarr[j];
        if (numarr[i] == 1 && i == digit)
            acc *= pow(9, i - 1);
        else
            acc *= (numarr[i] - 1) * pow(9, i - 1);
        ans = max(acc, ans);
    }
    printf("%d", ans);
    return 0;
}