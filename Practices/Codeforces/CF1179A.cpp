// CF1179A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, q;
vector<deque<int> /**/> steps, loop;
deque<int> curt;

void output(deque<int> &rhs)
{
    for (auto x : rhs)
        printf("%d ", x);
    puts("");
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1, val; i <= n; i++)
        scanf("%d", &val), curt.push_back(val);
    int max_val = *max_element(curt.begin(), curt.end());
    steps.push_back(deque<int>{curt[0], curt[1]});
    while (curt[0] != max_val)
    {
        int A = curt[0], B = curt[1];
        curt.pop_front(), curt.pop_front();
        curt.push_front(max(A, B)), curt.push_back(min(A, B));
        steps.push_back(deque<int>{curt[0], curt[1]});
    }
    loop.push_back(steps.back()), steps.pop_back();
    for (int i = 1; i <= n - 2; i++)
    {
        int A = curt[0], B = curt[1];
        curt.pop_front(), curt.pop_front();
        curt.push_front(max(A, B)), curt.push_back(min(A, B));
        loop.push_back(deque<int>{curt[0], curt[1]});
    }
    int rem = steps.size(), seg = loop.size();
    while (q--)
    {
        ll val;
        scanf("%lld", &val), val--;
        if (val < rem)
            printf("%d %d\n", steps[val][0], steps[val][1]);
        else
            val -= rem, printf("%d %d\n", loop[val % seg][0], loop[val % seg][1]);
    }
    return 0;
}