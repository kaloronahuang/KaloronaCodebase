// A.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 2000;
int n, arr[MAX_N], ans_arr[MAX_N];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    int pt = 0;
    for (int i = 1; i <= n; i++)
        if (arr[i] == arr[i - 1])
            ans_arr[pt]++;
        else
            ans_arr[++pt] = 1;
    int ans = 0;
    for (int i = 2; i <= pt; i++)
        ans = max(ans, min(ans_arr[i - 1], ans_arr[i]) * 2);
    printf("%d", ans);
    return 0;
}