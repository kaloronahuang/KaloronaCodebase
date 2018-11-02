// P1594.cpp
#include <iostream>
#include <iomanip>

using namespace std;

#define ll long long
const double INF = 9223372036854775807ll;
const ll maxn = 1100;
struct car
{
    double v, w;
} cars[maxn];
double W, L, N;
double F[maxn];

void DP()
{
    F[0] = 0;
    for (ll i = 1; i <= N; i++)
    {
        F[i] = (double)INF;
        double load = 0;
        double lspd = INF;
        for (ll j = i; j > 0; j--)
        {
            load += cars[j].w;
            if (load > W)
                break;
            lspd = min(lspd, cars[j].v);
            F[i] = min(F[i], F[j - 1] + L / lspd);
        }
    }
}

int main()
{
    cin >> W >> L >> N;
    for (ll i = 1; i <= N; i++)
        cin >> cars[i].w >> cars[i].v;
    DP();
    cout << fixed << setprecision(1) << F[(ll)N] * 60;
    return 0;
}