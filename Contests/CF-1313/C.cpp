// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

typedef long long ll;

int n, mi[MAX_N], stk[MAX_N];
ll pre[MAX_N], suf[MAX_N];
int wi[MAX_N];
vector<int> rig;
stack<int> lft;

void goLft(int pos, int pre)
{
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &mi[i]);
    ll ans = 0, pos = 0;
    for (int rd = 0; rd < 2; rd++)
    {
        int tail = 0;
        ll acc = 0;
        for (int i = 1; i <= n; i++)
        {
            int w = 0;
            while (tail && stk[tail] > mi[i])
                acc -= 1LL * wi[tail] * stk[tail], w += wi[tail--];
            stk[++tail] = mi[i], wi[tail] = w + 1, acc += 1LL * wi[tail] * stk[tail];
            if (rd == 0)
                pre[i] = acc;
            else
                suf[i] = acc;
        }
        reverse(mi + 1, mi + 1 + n);
    }
    for (int i = 1; i <= n; i++)
    {
        ll tmp = pre[i] + suf[n - i + 1] - mi[i];
        if (tmp > ans)
            ans = tmp, pos = i;
    }
    for (int i = pos - 1, pre = mi[pos]; i >= 1; i--)
        pre = min(pre, mi[i]), lft.push(pre);
    while (!lft.empty())
        printf("%d ", lft.top()), lft.pop();
    printf("%d ", mi[pos]);
    for (int i = pos + 1, pre = mi[pos]; i <= n; i++)
        pre = min(pre, mi[i]), printf("%d ", pre);
    puts("");
    return 0;
}