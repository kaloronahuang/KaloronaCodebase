// queue.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int q;
char cmdlet[10];

struct operation
{
    int typ, ti, ai, di;

    bool operator<(const operation &rhs) const { return ti < rhs.ti; }
};
multiset<operation> ms;

void subtask1()
{
    while (q--)
    {
        int Ti, Ai, Di;
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'a' && cmdlet[2] == 'd' && cmdlet[5] == 'b')
            scanf("%d%d", &Ti, &Ai), ms.insert(operation{1, Ti, Ai, 0});
        else if (cmdlet[1] == 'a' && cmdlet[2] == 'd' && cmdlet[5] == 'f')
            scanf("%d%d", &Ti, &Ai), ms.insert(operation{2, Ti, Ai, 0});
        else if (cmdlet[1] == 'd' && cmdlet[5] == 'b')
            scanf("%d", &Ti), ms.insert(operation{3, Ti, 0, 0});
        else if (cmdlet[1] == 'd' && cmdlet[5] == 'f')
            scanf("%d", &Ti), ms.insert(operation{4, Ti, 0, 0});
        else if (cmdlet[1] == 'a' && cmdlet[2] == 's')
        {
            scanf("%d%d", &Ti, &Di);
            deque<int> dq;
            for (auto &x : ms)
            {
                if (x.ti > Ti)
                    break;
                switch (x.typ)
                {
                case 1:
                    dq.push_back(x.ai);
                    break;
                case 2:
                    dq.push_front(x.ai);
                    break;
                case 3:
                    dq.pop_back();
                    break;
                case 4:
                    dq.pop_front();
                    break;
                }
            }
            if (dq.size() < Di)
                puts("none");
            else
                printf("%d\n", (cmdlet[5] == 'b' ? *(dq.rbegin() + Di) : *(dq.begin() + Di)));
        }
        else
        {
            // clear;
            scanf("%d", &Ti);
            ms.erase(operation{0, Ti, 0, 0});
        }
    }
}

int main()
{
    scanf("%d", &q), subtask1();
    return 0;
}