// P1036.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int n, k;
int arr[5000010];
bool e_prime[5000010];

void sort_prime()
{
    memset(e_prime, true, sizeof(e_prime));
    for (int i = 2; i < 5000010; i++)
        if (e_prime[i] == true)
            for (int j = 2; i * j < 5000010; j++)
                e_prime[j * i] = false;
}

void init()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

int ans = 0;

void DFS(int step, int dep, int sum)
{
    if (dep == k)
    {
        if (e_prime[sum])
            ans++;
        return;
    }
    if (step == n)
        return;
    DFS(step + 1, dep + 1, sum + arr[step]);
    DFS(step + 1, dep, sum);
}

int main()
{
    sort_prime();
    init();
    DFS(0, 0, 0);
    cout << ans;
    return 0;
}