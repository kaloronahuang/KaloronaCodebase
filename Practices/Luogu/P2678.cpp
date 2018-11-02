// P2678.cpp
#include <iostream>

using namespace std;

const int maxn = 500020;
int L, N, M;
int D[maxn];

bool check(int num)
{
    int last = 0;
    int cnt = 0;
    for (int i = 0; i <= N; i++)
        if (D[i] - last < num)
            cnt++;
        else
            last = D[i];
    if (cnt > M)
        return false;
    return true;
}

void solve()
{
    int left = 0;
    int right = L;
    int ans = 0;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (check(mid))
            left = mid + 1, ans = mid;
        else
            right = mid - 1;
    }
    cout << ans;
}

int main()
{
    cin >> L >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> D[i];
    D[N] = L;
    solve();
    return 0;
}