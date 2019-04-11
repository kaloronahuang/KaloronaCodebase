// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1010;
vector<int> vecX[MAX_N], vecY[MAX_N];
int arr[MAX_N][MAX_N], n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &arr[i][j]), vecX[i].push_back(arr[i][j]), vecY[j].push_back(arr[i][j]);
    for (int i = 1; i <= n; i++)
        sort(vecX[i].begin(), vecX[i].end()), vecX[i].erase(unique(vecX[i].begin(), vecX[i].end()), vecX[i].end());
    for (int i = 1; i <= m; i++)
        sort(vecY[i].begin(), vecY[i].end()), vecY[i].erase(unique(vecY[i].begin(), vecY[i].end()), vecY[i].end());
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int greater_1 = vecX[i].end() - lower_bound(vecX[i].begin(), vecX[i].end(), arr[i][j]) - 1;
            int greater_2 = vecY[j].end() - lower_bound(vecY[j].begin(), vecY[j].end(), arr[i][j]) - 1;
            int lower_1 = lower_bound(vecX[i].begin(), vecX[i].end(), arr[i][j]) - vecX[i].begin();
            int lower_2 = lower_bound(vecY[j].begin(), vecY[j].end(), arr[i][j]) - vecY[j].begin();
            printf("%d ", max(lower_1, lower_2) + 1 + max(greater_1, greater_2));
        }
        puts("");
    }
    return 0;
}