// POJ2823.cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 1e6 + 100;
int n, k, seq[maxn], maxseq[maxn], minseq[maxn];
int main()
{

    while (~scanf("%d%d", &n, &k))
    {
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]);
        deque<int> qmax, qmin;
        for (int i = 1; i <= n; i++)
        {
            while (!qmin.empty() && seq[qmin.back()] > seq[i])
                qmin.pop_back();
            qmin.push_back(i);
            if (i >= k)
            {
                while (!qmin.empty() && qmin.front() <= i - k)
                    qmin.pop_front();
                minseq[i] = qmin.front();
            }

            while (!qmax.empty() && seq[qmax.back()] < seq[i])
                qmax.pop_back();
            qmax.push_back(i);
            if (i >= k)
            {
                while (!qmax.empty() && qmax.front() <= i - k)
                    qmax.pop_front();
                maxseq[i] = qmax.front();
            }
        }
        for (int i = k; i <= n; i++)
            printf("%d ", seq[minseq[i]]);
        printf("\n");
        for (int i = k; i <= n; i++)
            printf("%d ", seq[maxseq[i]]);
        printf("\n");
    }
    return 0;
}