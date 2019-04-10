// D.cpp
#include <bits/stdc++.h>
#define ll long long
#define pr pair<ll, ll>
using namespace std;
const int MAX_N = 10100;
ll seqA[MAX_N], seqB[MAX_N], seqC[MAX_N], x, y, z, k, current_seq[MAX_N << 2], tmp[MAX_N << 2];
struct node
{
    ll val, ptr1, ptr2;
    bool operator<(const node &nd) const { return val < nd.val; }
};
priority_queue<node> pq;
bool cmp(ll a, ll b) { return a > b; }
void solve(ll *seq)
{
    pq.push(node{current_seq[1] + seq[1], 1, 1});
    memset(tmp, 0, sizeof(tmp));
    for (int i = 1; i <= k && (!pq.empty()); i++)
    {
        node curt = pq.top();
        tmp[i] = curt.val, pq.pop();
        if (curt.ptr2 == 1 && current_seq[curt.ptr1 + 1] != 0)
            pq.push(node{current_seq[curt.ptr1 + 1] + seq[curt.ptr2], curt.ptr1 + 1, curt.ptr2});
        if (seq[curt.ptr2 + 1] != 0)
            pq.push(node{current_seq[curt.ptr1] + seq[curt.ptr2 + 1], curt.ptr1, curt.ptr2 + 1});
    }
    memcpy(current_seq, tmp, sizeof(tmp));
    while (!pq.empty())
        pq.pop();
}
int main()
{
    scanf("%d%d%d%d", &x, &y, &z, &k);
    for (int i = 1; i <= x; i++)
        scanf("%lld", &seqA[i]);
    for (int i = 1; i <= y; i++)
        scanf("%lld", &seqB[i]);
    for (int i = 1; i <= z; i++)
        scanf("%lld", &seqC[i]);
    sort(seqA + 1, seqA + 1 + x, cmp), sort(seqB + 1, seqB + 1 + y, cmp), sort(seqC + 1, seqC + 1 + z, cmp);
    for (int i = 1; i <= k; i++)
        current_seq[i] = seqA[i];
    solve(seqB), solve(seqC);
    for (int i = 1; i <= k; i++)
        printf("%lld\n", current_seq[i]);
    return 0;
}