// AT1878.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

struct node
{
    ll ai, bi, val;
} nodes[MAX_N];

int n;
vector<node> alpha, beta;

bool compareAlpha(node A, node B) { return A.ai < B.ai; }
bool compareBeta(node A, node B) { return A.bi > B.bi; }

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &nodes[i].ai, &nodes[i].bi), nodes[i].val = nodes[i].ai - nodes[i].bi;
    for (int i = 1; i <= n; i++)
        if (nodes[i].val <= 0)
            alpha.push_back(nodes[i]);
        else
            beta.push_back(nodes[i]);
    sort(alpha.begin(), alpha.end(), compareAlpha);
    sort(beta.begin(), beta.end(), compareBeta);
    ll prefix = 0, ans = 0;
    for (int i = 0, siz = alpha.size(); i < siz; i++)
        ans = max(ans, prefix + alpha[i].ai), prefix += alpha[i].val;
    for (int i = 0, siz = beta.size(); i < siz; i++)
        ans = max(ans, prefix + beta[i].ai), prefix += beta[i].val;
    printf("%lld", ans);
    return 0;
}