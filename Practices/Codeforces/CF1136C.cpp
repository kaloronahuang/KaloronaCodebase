// CF1136C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 550;
vector<int> diagA[MAX_N << 1], diagB[MAX_N << 1];
int n, m, tmpx;
int main()
{
    scanf("%d%d", &n, &m);
    ;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &tmpx), diagA[i + j].push_back(tmpx);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &tmpx), diagB[i + j].push_back(tmpx);
    for (int i = 2; i <= n + m; i++)
    {
        sort(diagA[i].begin(), diagA[i].end());
        sort(diagB[i].begin(), diagB[i].end());
        if (diagA[i] != diagB[i])
            printf("NO"), exit(0);
    }
    printf("YES");
    return 0;
}