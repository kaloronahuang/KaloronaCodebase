// P2429.cpp
#include <cstdio>
#include <iostream>

using namespace std;
int arr[25], n, m, ans;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
        for (int j = arr[i]; j <= m; j += arr[i])
        {
            bool ck = true;
            for (int k = 1; k < i; k++)
                if (j % arr[k] == 0)
                {
                    ck = false;
                    break;
                }
            if (ck)
                ans += j, ans %= 376544743;
        }
    }
    printf("%d", ans);
    return 0;
}