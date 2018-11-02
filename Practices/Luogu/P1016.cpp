// P1016.cpp
// tag:DP

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iomanip>

using namespace std;

const int INF = 0x7fffffff;
double petrol_d[10];
double petrol_p[10];
double D1, C, D2, P;
int N;

void init()
{
    cin >> D1 >> C >> D2 >> P >> N;
    petrol_d[0] = 0;
    petrol_p[0] = P;
    for (int i = 1; i <= N; i++)
        cin >> petrol_d[i] >> petrol_p[i];
    petrol_d[N + 1] = D1;
}

void solve()
{
    double last = 0;
    for (int i = 0; i <= N; i++)
    {
        if (petrol_d[i] - last > C * D2)
        {
            cout << "No Solution";
            return;
        }
        last = petrol_d[i];
    }
    last = 0;
    double cost = 0;
    double tank_now = 0;

    for (int i = 0; i <= N + 1; i++)
    {
        // Find the petrol stat;
        double min_val = INF;
        int min_id = -1;
        for (int j = i + 1; j <= N + 1; j++)
            if (C * D2 < petrol_d[j] - petrol_d[i])
                break;
            else if (min_val > petrol_p[j])
                min_val = petrol_p[j], min_id = j;
        // Judge;
        if (min_id == -1 && i == N + 1)
            break;
        if (min_val <= petrol_p[i])
        {
            cost += ((petrol_d[min_id] - petrol_d[i]) / D2 - tank_now) * petrol_p[i];
            tank_now = 0;
            i = min_id - 1;
        }
        else
        {
            cost += (C - tank_now) * petrol_p[i];
            tank_now = C - (petrol_d[min_id] - petrol_d[i]) / D2;
            i = min_id - 1;
        }
    }
    cout << fixed << setprecision(2) << cost;
}

int main()
{
    init();
    solve();
    return 0;
}