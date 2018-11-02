// P1095.cpp
// tag:DP
#include <iostream>
#include <cstring>

using namespace std;

int M, S, T;
int timeline[300020];

void solve()
{
    timeline[0] = 0;
    for (int i = 1; i <= T; i++)
        if (M >= 10)
            timeline[i] = timeline[i - 1] + 60, M -= 10;
        else
            timeline[i] = timeline[i - 1], M += 4;
    for (int i = 1; i <= T; i++)
    {
        timeline[i] = max(timeline[i], timeline[i - 1] + 17);
        if (timeline[i] >= S)
        {
            cout << "Yes" << endl
                 << i;
            break;
        }
    }
    if (timeline[T] < S)
        cout << "No" << endl
             << timeline[T];
}

int main()
{
    cin >> M >> S >> T;
    solve();
    return 0;
}