// P1134.cpp
#include <bits/stdc++.h>
using namespace std;
int num, ans = 1, arr[4] = {6, 8, 4, 2};
int main()
{
    scanf("%d", &num);
    while (num)
    {
        for (int i = 1; i <= num % 10; i++)
            if (i != 5)
                ans = ans * i % 10;
        num = num / 5;
        ans = ans * arr[num % 4] % 10;
    }
    printf("%d", ans);
    return 0;
}