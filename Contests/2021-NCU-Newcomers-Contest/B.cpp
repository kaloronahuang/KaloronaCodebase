// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 210;
const char *hello = "hello";
const char *world = "world";

char str[MAX_N];

int main()
{
    cin.getline(str + 1, MAX_N);
    int ans1 = 0, ans2 = 0, len = strlen(str + 1);
    for (int i = 5; i <= len; i++)
    {
        bool flag = true;
        for (int offset = 0; offset < 5; offset++)
            flag &= (str[i - 4 + offset] == hello[offset]);
        if (flag)
            ans1++;
    }
    for (int i = 5; i <= len; i++)
    {
        bool flag = true;
        for (int offset = 0; offset < 5; offset++)
            flag &= (str[i - 4 + offset] == world[offset]);
        if (flag)
            ans2++;
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}