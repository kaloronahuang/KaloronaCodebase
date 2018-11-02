// P1233.cpp
#include <iostream>
#include <algorithm>

using namespace std;

int n;
struct stick
{
    int w, l;
    stick() {}
    stick(int w_, int l_) : w(w_), l(l_) {}
} st[5010];

bool cmp(stick a, stick b)
{
    if (a.l == b.l)
        return a.w >= b.w;
    return a.l > b.l;
}

bool cmp_(int a, int b)
{
    return a > b;
}

int getLIS()
{
    int ws[n + 1];
    int seq[n + 1];
    for (int i = 1; i <= n; i++)
        ws[i] = st[i].w;
    int cur = 0;
    seq[0] = -1;
    for (int i = 1; i <= n; i++)
        if (ws[i] > seq[cur])
            seq[++cur] = ws[i];
        else
            *(lower_bound(seq, seq + cur, ws[i])) = ws[i];
    return cur;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> st[i].l >> st[i].w;
    sort(st + 1, st + n + 1, cmp);
    cout << getLIS();
    return 0;
}