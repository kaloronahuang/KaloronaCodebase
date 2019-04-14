// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 110;
int n, m, k, power[MAX_N], aff[MAX_N], tmpx, chosen;
int presentative[MAX_N];
vector<int> students[MAX_N];
bool compare(int a, int b)
{
    return power[a] > power[b];
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &power[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmpx), aff[i] = tmpx, students[tmpx].push_back(i);
    for (int i = 1; i <= m; i++)
        sort(students[i].begin(), students[i].end(), compare);
    int ans = 0;
    for (int i = 1; i <= k; i++)
    {
        scanf("%d", &tmpx);
        if (students[aff[tmpx]][0] != tmpx)
            ans++;
    }
    printf("%d", ans);
    return 0;
}