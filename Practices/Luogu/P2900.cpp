// P2900.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 5e4 + 200;

int n, tot, q[MAX_N], head, tail;
ll dp[MAX_N];

struct rect
{
    int height, width;
    bool operator<(const rect &nd) const { return height < nd.height || (height == nd.height && width < nd.width); }
} rects[MAX_N], nodes[MAX_N];

vector<rect> vec;

double slopeFunc(int A, int B) { return double(dp[A] - dp[B]) / double(nodes[B + 1].width - nodes[A + 1].width); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &rects[i].height, &rects[i].width);
    sort(rects + 1, rects + 1 + n);
    for (int cur = n; cur >= 1;)
    {
        int j = cur;
        while (rects[cur].height >= rects[j].height && rects[cur].width >= rects[j].width && j >= 1)
            j--;
        nodes[++tot] = rects[cur], cur = j;
    }
    reverse(nodes + 1, nodes + 1 + tot), n = tot;

    head = 1, tail = 1, q[1] = 0;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && slopeFunc(q[head], q[head + 1]) < nodes[i].height)
            head++;
        dp[i] = dp[q[head]] + 1LL * nodes[i].height * nodes[q[head] + 1].width;
        while (head < tail && slopeFunc(q[tail], i) < slopeFunc(q[tail - 1], q[tail]))
            tail--;
        q[++tail] = i;
    }

    printf("%lld", dp[n]);
    return 0;
}