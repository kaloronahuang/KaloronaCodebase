// P2168.cpp
// tag:Huffman
#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const int maxn = 100200;
ll n, k, weights[maxn];
struct node
{
    ll val, mergeTimes;
    bool operator<(const node &nd) const
    {
        return val > nd.val || (val == nd.val) && (mergeTimes > nd.mergeTimes);
    }
};
priority_queue<node> seq;
int main()
{
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &weights[i]), seq.push(node{weights[i], 0});
    ll numOfZero = (k - 1) - (n - 1) % (k - 1);
    numOfZero %= (k - 1);
    for (int i = 0; i < numOfZero; i++)
        seq.push(node{0, 0});
    ll ans = 0, maxans = 0, L = 1;
    for (L = 1; seq.size() != 1; L++)
    {
        int siz = seq.size();
        ll curt = 0, max_val = 0;
        for (int i = 0; i < k; i++)
            curt += seq.top().val, max_val = max(max_val, seq.top().mergeTimes + 1), seq.pop();
        ans += curt, seq.push(node{curt, max_val}), maxans = max(maxans, max_val);
    }
    printf("%lld\n%lld", ans, maxans);
    return 0;
}