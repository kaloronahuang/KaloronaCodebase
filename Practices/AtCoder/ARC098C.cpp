// ARC098C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

typedef pair<int, int> pii;

int n, k, q, ai[MAX_N], ans = 1e9;

int check(int minimum_val)
{
    vector<int> block, pool;
    for (int i = 1; i <= n + 1; i++)
        if (ai[i] >= minimum_val)
            block.push_back(ai[i]);
        else
        {
            if (block.size() >= k)
            {
                sort(block.begin(), block.end());
                int len = block.size();
                for (int i = 0; i <= len - k; i++)
                    pool.push_back(block[i]);
            }
            block.clear();
        }
    sort(pool.begin(), pool.end());
    if (pool.size() < q)
        return 1e9;
    return pool[q - 1] - minimum_val;
}

int main()
{
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        ans = min(ans, check(ai[i]));
    printf("%d\n", ans);
    return 0;
}