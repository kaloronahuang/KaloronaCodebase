// BZ3629.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, n, primes[MAX_N], ptot;
bool vis[MAX_N];
vector<int> ans;

bool checkPrime(int x)
{
    for (int i = 2; 1LL * i * i <= x; i++)
        if (x % i == 0)
            return false;
    return true;
}

void dfs(int pos, int current, int sum)
{
    if (sum == 1)
        return (void)(ans.push_back(current));
    if (sum - 1 > primes[pos] && checkPrime(sum - 1))
        ans.push_back(1LL * current * (sum - 1));
    for (int i = pos + 1; 1LL * primes[i] * primes[i] <= sum; i++)
        for (int acc = primes[i] + 1, curt = primes[i]; acc <= sum; curt *= primes[i], acc += curt)
            if (sum % acc == 0)
                dfs(i, current * curt, sum / acc);
}

int main()
{
    for (int i = 2; i < MAX_N; i++)
    {
        if (vis[i] == false)
            primes[++ptot] = i;
        for (int j = 1; j <= ptot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
    while (scanf("%d", &n) != EOF)
    {
        ans.clear();
        dfs(0, 1, n), sort(ans.begin(), ans.end());
        printf("%d\n", int(ans.size()));
        for (auto x : ans)
            printf("%d ", x);
        if (ans.size() != 0)
            puts("");
    }
    return 0;
}