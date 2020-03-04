// CF1103B.cpp
#include <bits/stdc++.h>

using namespace std;

char cmdlet[20];

bool readStatus() { return scanf("%s", cmdlet + 1), cmdlet[1] != 'e'; }

bool query(int x, int y)
{
    printf("? %d %d\n", x, y), fflush(stdout);
    scanf("%s", cmdlet + 1);
    return cmdlet[1] == 'x';
}

void answer(int x) { printf("! %d\n", x), fflush(stdout); }

int main()
{
    while (readStatus())
    {
        int highest_digit = -1;
        for (int i = 0; i <= 30; i++)
            if (query(i == 0 ? 0 : 1 << (i - 1), 1 << i))
            {
                highest_digit = i - 1;
                break;
            }
        int ans = highest_digit == -1 ? 0 : (1 << highest_digit);
        for (int i = highest_digit - 1; i >= 0; i--)
            if (!query(ans, ans | (1 << i)))
                ans |= (1 << i);
        ans++, answer(ans);
    }
    return 0;
}