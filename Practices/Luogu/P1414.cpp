// P1414.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e6 + 200;
int arr[MAX_N], n, bucket[MAX_N], limit;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]), limit = max(arr[i], limit);
        for (int j = 1; j * j <= arr[i]; j++)
            if (arr[i] % j == 0)
                if (j * j == arr[i])
                    bucket[j]++;
                else
                    bucket[j]++, bucket[arr[i] / j]++;
    }
    int last = limit;
    for (int i = 1; i <= n; i++)
    {
        while (bucket[last] < i)
            last--;
        printf("%d\n", last);
    }
    return 0;
}