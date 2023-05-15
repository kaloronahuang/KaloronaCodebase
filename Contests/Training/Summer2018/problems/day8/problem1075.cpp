#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    double x;
    int n;
    double res;
    cin >> x >> n;
    res = x;
    for(int i = 1;i<=n;i++)
    {
        res = sqrt(res+i);
    }
    cout << fixed << setprecision(2) << res;
    return 0;
}