// P1563.cpp
#include <iostream>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    int dir[N];
    string occupations[N];
    int cmdKeys[M];
    int cmdPath[M];
    // I/O;
    for (int i = 0; i < N; i++)
        cin >> dir[i] >> occupations[i];
    for (int j = 0; j < M; j++)
        cin >> cmdKeys[j] >> cmdPath[j];
    // Process;
    int currentBias = 0;
    for (int i = 0; i < M; i++)
        if (cmdKeys[i] == 0)
            if (dir[currentBias % N] == 1)
                currentBias += cmdPath[i];
            else
            {
                currentBias -= cmdPath[i];
                if (currentBias < 0)
                    currentBias = N + currentBias;
            }
        else if (dir[currentBias % N] == 1)
        {
            currentBias -= cmdPath[i];
            if (currentBias < 0)
                currentBias = N + currentBias;
        }
        else
            currentBias += cmdPath[i];
    cout << occupations[currentBias % N];
    return 0;
}