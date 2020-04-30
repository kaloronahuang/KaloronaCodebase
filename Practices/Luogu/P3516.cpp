// P3516.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

typedef pair<int, int> pii;

int n, ai[MAX_N], last_pos;
vector<pii> ansBox;

void moveAround(int pos)
{
    if (pos == last_pos)
        return;
    ansBox.push_back(make_pair((last_pos - pos + n) % n, 0));
    last_pos = pos;
}

void move1(int pos)
{
    moveAround(pos - 1);
    ansBox.push_back(make_pair(2, 1));
    swap(ai[pos], ai[pos - 1]), swap(ai[pos], ai[pos + 1]);
}

void move2(int pos)
{
    moveAround(pos - 2);
    ansBox.push_back(make_pair(1, 1));
    swap(ai[pos], ai[pos - 1]), swap(ai[pos - 1], ai[pos - 2]);
}

int main()
{
    scanf("%d", &n), last_pos = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    if (n == 1)
        puts("0"), exit(0);
    if (n == 2)
        if (ai[1] < ai[2])
            puts("0"), exit(0);
        else
            puts("1\n1a"), exit(0);
    for (int val = 1, pos; val <= n - 2; val++)
    {
        pos = 0;
        for (int i = val; i <= n && pos == 0; i++)
            if (ai[i] == val)
                pos = i;
        if (pos == val)
            continue;
        // begin to adjust;
        while (pos - val > 1)
            move2(pos), pos -= 2;
        if (pos - val >= 1)
            move1(pos), pos--;
    }
    if (ai[n - 1] == n)
    {
        if (n & 1)
            puts("NIE"), exit(0);
        int pos = n - 1;
        while (pos > 1)
            move2(pos), pos -= 2;
    }
    int pos = 1;
    for (int i = 1; i <= n; i++)
        if (ai[i] == 1)
            pos = i;
    moveAround(pos);
    printf("%lld\n", 1LL * ansBox.size());
    for (pii u : ansBox)
        if (u.second == 0)
            printf("%da ", u.first);
        else
            printf("%db ", u.first);
    return 0;
}