// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int remDomain[10] = {1, 2, 4, 8, 1, 3, 6, 1, 2, 5}, mod = 1e9 + 8;

const int pre[31] = {0, 3, 12, 34, 78, 156, 282, 471, 744, 1119, 1623, 2279, 3118, 4167, 5463, 7039, 8935, 11188, 13845, 16946, 20545, 24685, 29424, 34812, 40911, 47775, 55472, 64060, 73612, 84190, 95874};

int n, L, ans1;
long long seq[int(1e5) + 200];

int main()
{
    scanf("%d%d", &n, &L);
    for (int i = 0; i <= n; i++)
        if (remDomain[i % 10] == L)
            ans1++;
    printf("%d ", ans1);
    for (int i = 1; i <= 30; i++)
        seq[i] = pre[i];
    for (int i = 31; i <= ans1; i++)
        seq[i] = (seq[n - 1] + seq[n - 2] - seq[n - 5] - seq[n - 6] - seq[n - 7] + seq[n - 8] + seq[n - 9] + seq[n - 10] - seq[n - 13] - seq[n - 14] + seq[n - 15]) % mod;
    printf("%lld", seq[ans1]);

    return 0;
}