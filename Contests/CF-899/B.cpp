// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int seq[48] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int n, arr[30];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for (int stpos = 0; stpos < 48; stpos++)
        for (int i = 0; i <= n; i++)
        {
            if (i == n)
                puts("Yes"), exit(0);
            else if (arr[i] != seq[(stpos + i) % 48])
                break;
        }
    puts("No");
    return 0;
}