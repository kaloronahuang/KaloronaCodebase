// ARC093B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int A, B;
bool flag;
char mp[MAX_N][MAX_N];

int main()
{
    // freopen("Table.out", "w", stdout);
    scanf("%d%d", &A, &B), printf("100 100\n");
    for (int i = 1; i <= 50; i++)
        for (int j = 1; j <= 100; j++)
            mp[i][j] = '#';
    for (int i = 51; i <= 100; i++)
        for (int j = 1; j <= 100; j++)
            mp[i][j] = '.';
    A--, B--;
    for (int i = 1; i <= 49 && A; i += 2)
        for (int j = (((i - 1) >> 1) & 1) ? 2 : 1; j <= 100 && A; j += 2)
            mp[i][j] = '.', A--;
    for (int i = 100; i >= 52 && B; i -= 2)
        for (int j = (((100 - i) >> 1) & 1) ? 2 : 1; j <= 100 && B; j += 2)
            mp[i][j] = '#', B--;
    for (int i = 1; i <= 100; i++)
        printf("%s\n", mp[i] + 1);
    return 0;
}