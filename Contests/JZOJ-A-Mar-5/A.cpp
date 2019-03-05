// A.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e6 + 2000;
int n, m, arr[MAX_N], blockId[MAX_N];
int currentId[MAX_N], bucket[MAX_N];
ll cnt[MAX_N], leftBucket[MAX_N], answer, anses[MAX_N];
struct query
{
    int l, r, id;
    bool operator<(const query &qu) const
    {
        return blockId[l] < blockId[qu.l] ||
               (blockId[l] == blockId[qu.l] && r < qu.r);
    }
} queries[MAX_N];
void update_left(int x)
{
    leftBucket[currentId[x]]++;
    answer = max(answer, (leftBucket[currentId[x]] + cnt[currentId[x]]) * 1LL * arr[x]);
}
int main()
{
    scanf("%d%d", &n, &m);
    int siz = sqrt(n * 1.0);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), bucket[i] = arr[i], blockId[i] = (i - 1) / siz + 1;
    sort(bucket + 1, bucket + 1 + n);
    int buckTot = unique(bucket + 1, bucket + 1 + n) - bucket;
    for (int i = 1; i <= n; i++)
        currentId[i] = lower_bound(bucket + 1, bucket + 1 + buckTot, arr[i]) - bucket;
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &queries[i].l, &queries[i].r), queries[i].id = i;
    sort(queries + 1, queries + 1 + m);
    int L = 1, R = 0, tmd;
    ll tmp = 0;
    answer = 0;
    queries[0].l = 0, blockId[0] = 0;
    for (int i = 1; i <= m; i++)
    {
        if (blockId[queries[i - 1].l] != blockId[queries[i].l])
        {
            memset(cnt, 0, sizeof(cnt));
            R = tmd = blockId[queries[i].l] * siz;
            answer = tmp = 0;
        }
        L = min(tmd + 1, queries[i].r + 1);
        while (L > queries[i].l)
            update_left(--L);
        while (R < queries[i].r)
        {
            R++;
            tmp = max((++cnt[currentId[R]]) * 1LL * arr[R], tmp);
            answer = max(answer, (cnt[currentId[R]] + leftBucket[currentId[R]]) * 1LL * arr[R]);
        }
        anses[queries[i].id] = answer;
        for (int j = L; j <= queries[i].r && j <= tmd; j++)
            leftBucket[currentId[j]]--;
        answer = tmp;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", anses[i]);
    return 0;
}