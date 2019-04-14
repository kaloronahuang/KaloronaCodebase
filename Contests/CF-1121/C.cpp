// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1010;
int n, k, arr[MAX_N];
struct task
{
    int currentTest, testAmount, aff, testId;
    bool operator<(const task &tsk) const
    {
        return testAmount - currentTest > tsk.testAmount - tsk.currentTest;
    }
} tasks[MAX_N], threads[MAX_N];
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]);
    deque<task> undone;
    for (int i = 1; i <= n; i++)
    {
        task curt;
        curt.currentTest = 1, curt.testAmount = arr[i];
        curt.testId = i, curt.aff = -1;
        undone.push_back(curt);
    }
    for (int i = 1; i <= min(k, n); i++)
    {
        task curt = undone.front();
        curt.aff = i, threads[i] = curt;
        undone.pop_front();
    }
    int completed = 0, answer = 0;
    while (completed != n)
    {
        int cmp_val = 0x3f3f3f3f;
        for (int i = 1; i <= k; i++)
            if (threads[i].aff && threads[i].currentTest <= threads[i].testAmount)
                cmp_val = min(cmp_val, threads[i].testAmount - threads[i].currentTest);
        int q = (int)(1.0 * 100 * completed / (1.0 * n) + 0.5);
        for (int i = 1; i <= k; i++)
            if (threads[i].aff != 0 && threads[i].currentTest <= threads[i].testAmount)
            {
                int lft = threads[i].currentTest, rig = threads[i].currentTest + cmp_val;
                if (lft <= q && q <= rig)
                    answer++;
                threads[i].currentTest += cmp_val;
                if (threads[i].currentTest == threads[i].testAmount)
                    completed++, threads[i].aff = 0;
                if (threads[i].currentTest == threads[i].testAmount && !undone.empty())
                {
                    // to change;
                    task tsk = undone.front();
                    undone.pop_front(), tsk.aff = i;
                    tsk.currentTest = 0, threads[i] = tsk;
                }
                threads[i].currentTest++;
            }
    }
    printf("%d", answer);
    return 0;
}