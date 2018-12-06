// POJ3784.cpp
#include <iostream>
#include <queue>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 10010;
int id, n, arr[maxn];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &id, &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &arr[i]);
        printf("%d %d\n", id, (n / 2) + 1);
        priority_queue<int> qmax;
        priority_queue< int, vector<int>, greater<int> > qmin;
        int cnt = 0;
        for (int key = 1; key <= n; key++)
            if (key & 1)
            {
                qmin.push(arr[key]);
                while (!qmax.empty() && qmin.top() < qmax.top())
                {
                    int stop = qmin.top(), btop = qmax.top();
                    qmin.pop(), qmin.push(btop), qmax.pop(), qmax.push(stop);
                }
                printf("%d ", qmin.top());
                if (++cnt % 10 == 0)
                    printf("\n");
            }
            else
                qmax.push(arr[key]);
        printf("\n");
    }
    return 0;
}