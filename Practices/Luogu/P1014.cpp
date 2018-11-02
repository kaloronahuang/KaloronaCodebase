// P1014.cpp
#include <iostream>
#include <algorithm>

using namespace std;

int n;
int x, y;
int pre[20000];

void getPos()
{
    int rpos = lower_bound(pre, pre + 20000, n) - pre;
    int lpos = rpos - 1;
}

int main()
{
    pre[0] = 3;
    for (int i = 1; i < 20000; i++)
        pre[i] = 2 * pre[i - 1] + 1;
    cin >> n;
}