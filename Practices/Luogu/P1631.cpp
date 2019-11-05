// P1631.cpp
#include <bits/stdc++.h>
typedef long long ll;
#define pr pair<ll, int>

using namespace std;

const int MAX_N = 100100;

int n, seq1[MAX_N], seq2[MAX_N], to[MAX_N];
priority_queue<pr> pq;
ll ans[MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq1[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq2[i]), pq.push(make_pair(-(seq1[1] + seq2[i]), i)), to[i] = 1;
    int cnt = n;
    while (cnt--)
    {
        printf("%lld ", -pq.top().first);
        int pos = pq.top().second;
        pq.pop(), pq.push(make_pair(-(seq1[++to[pos]] + seq2[pos]), pos));
    }
    return 0;
}