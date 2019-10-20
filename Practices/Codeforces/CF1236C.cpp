// CF1236C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 90010;

int n;
vector<int> seq[330];

int main()
{
    scanf("%d", &n);
    int cnt = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i & 1)
            for (int j = 1; j <= n; j++)
                seq[j].push_back(cnt++);
        else
            for (int j = n; j >= 1; j--)
                seq[j].push_back(cnt++);
    }
    for (int i = 1; i <= n; i++, puts(""))
        for (int j = 0; j < n; j++)
            printf("%d ", seq[i][j]);
    return 0;
}