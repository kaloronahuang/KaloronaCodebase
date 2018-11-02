// P1233_ext.cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 5010;
struct stick
{
    int l, r;

    bool operator<(const stick &st) const
    {
        return (l == st.l) ? r > st.r : l < st.l;
    }
} sts[maxn];
int n;

bool cmp(stick a, stick b)
{
    return a.l < b.l;
}

void solve()
{
    sort(sts, sts + n, cmp);
    int seq[n];
    seq[0] = sts[0].r;
    int ans = 0;
    for (int i = 1; i < n; i++)
        if (seq[ans] < sts[i].r)
            seq[++ans] = sts[i].r;
        else
            *(lower_bound(seq, seq + ans, sts[i].r)) = sts[i].r;
    cout << ans;
}

void init()
{
    cin >> n;
    for (int i = 0; i<n; cin>> sts[i].l >> sts[i++].r)
        ;
}

int main()
{
    init();
    solve();
    return 0;
}