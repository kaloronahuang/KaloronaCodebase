// P1031.cpp
#include <iostream>

using namespace std;

int main()
{
    int N;
    cin >> N;
    int avg = 0, paris[N];
    for (int i = 0; i < N; i++)
    {
        cin >> paris[i];
        avg += paris[i];
    }
    avg = avg / N;
    for (int i = 0; i < N; i++)
        paris[i] -= avg;
    int cnt = 0;
    for (int x = 0; x < N; x++)
        if (paris[x] != 0)
        {
            paris[x + 1] += paris[x];
            paris[x] = 0;
            cnt++;
        }
    cout << cnt;
    return 0;
}