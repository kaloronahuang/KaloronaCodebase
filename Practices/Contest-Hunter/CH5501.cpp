// CH5501.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e6 + 200;
int n, ans, arr[MAX_N << 1];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), arr[i + n] = arr[i];
    deque<int> q;
    for (int i = 1; i <= 2 * n; i++)
    {
        while (!q.empty() && q.front() <= i - n / 2)
            q.pop_front();
        if (!q.empty())
            ans = max(ans, i - q.front() + arr[q.front()] + arr[i]);
        while (!q.empty() && arr[q.back()] - q.back() <= arr[i] - i)
            q.pop_back();
        q.push_back(i);
    }
    printf("%d", ans);
    return 0;
}