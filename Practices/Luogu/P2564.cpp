// P2564.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct node
{
    ll typ, val, dep;
    bool operator<(const node &nd) const { return val < nd.val; }
};
int n, k;
vector<int> typs[100];
multiset<node> st;

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++)
    {
        int ti;
        scanf("%d", &ti);
        while (ti--)
        {
            int num;
            scanf("%d", &num), typs[i].push_back(num);
        }
        st.insert(node{i, typs[i][0], 0});
    }
    ll ans = 0x3f3f3f3f3f3f3f3f;
    int full = 0;
    while (full < k)
    {
        node small = *st.begin(), biggest = *(--st.end());
        ans = min(ans, biggest.val - small.val);
        st.erase(st.begin());
        if (small.dep + 1 < typs[small.typ].size())
            small.val = typs[small.typ][small.dep + 1], small.dep++;
        else
            full++;
        st.insert(small);
    }
    node small = *st.begin(), biggest = *(--st.end());
    ans = min(ans, biggest.val - small.val);
    printf("%lld", ans);
    return 0;
}