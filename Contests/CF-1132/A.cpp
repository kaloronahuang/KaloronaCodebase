// A.cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[5];
int main()
{
    for (int i = 1; i <= 4; i++)
        cin >> cnt[i];
    if (cnt[1] == 0 && cnt[3])
        printf("0");
    else if (cnt[1] == cnt[4])
        printf("1");
    else
        printf("0");
    return 0;
}