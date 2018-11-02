// P1280.cpp
// DP;
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x7fffffff;
int N, K;

struct task
{
    int P, T;
    bool operator<(const task &tsk) const
    {
        if (P == tsk.P)
            return T < tsk.T;
        return P < tsk.P;
    }
} tasks[10010];

int F[10010];

void init()
{
    cin >> N >> K;
    for (int i = 0; i < K; i++)
        cin >> tasks[i].P >> tasks[i].T;
    sort(tasks, tasks + K);
}

int genDP()
{
    int cursor = K - 1;
    F[N + 1] = 0;
    for (int i = N; i > 0; i--)
        if (tasks[cursor].P == i)
            for (; cursor > -1; cursor--)
                if (tasks[cursor].P != i)
                    break;
                else
                    F[i] = max(F[i], F[i + tasks[cursor].T]);
        else
            F[i] = F[i + 1] + 1;
}

int main()
{
    init();
    genDP();
    cout << F[1];
    return 0;
}