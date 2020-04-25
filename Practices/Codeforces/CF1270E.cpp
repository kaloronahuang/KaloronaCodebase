// CF1270E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, xi[MAX_N], yi[MAX_N], tot, bucket[4];

struct segment
{
    ll len;
    int x, y;
    bool operator<(const segment &rhs) const { return len < rhs.len; }
} segs[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]), xi[i] += 1e6, yi[i] += 1e6;
    vector<int> ansBox;
    while (true)
    {
        memset(bucket, 0, sizeof(bucket));
        for (int i = 1; i <= n; i++)
            bucket[(xi[i] & 1) | ((yi[i] & 1) << 1)]++;
        if (bucket[0] == n || bucket[1] == n || bucket[2] == n || bucket[3] == n)
        {
            for (int i = 1; i <= n; i++)
                xi[i] >>= 1, yi[i] >>= 1;
            continue;
        }
        if (bucket[0] + bucket[3] > 0 && bucket[1] + bucket[2] > 0)
        {
            for (int i = 1; i <= n; i++)
                if (((xi[i] & 1) | ((yi[i] & 1) << 1)) == 0 || ((xi[i] & 1) | ((yi[i] & 1) << 1)) == 3)
                    ansBox.push_back(i);
            break;
        }
        else
        {
            for (int i = 0; i < 3; i++)
                if (bucket[i] > 0)
                {
                    for (int j = 1; j <= n; j++)
                        if (((xi[j] & 1) | ((yi[j] & 1) << 1)) == i)
                            ansBox.push_back(j);
                    break;
                }
            break;
        }
    }
    printf("%lld\n", 1LL * ansBox.size());
    for (int x : ansBox)
        printf("%d ", x);
    return 0;
}