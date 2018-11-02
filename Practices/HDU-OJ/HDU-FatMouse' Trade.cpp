// HDU-FatMouse' Trade.cpp
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 5000;
struct Commodity
{
    double price, val;
    double ratio;

    bool operator<(const Commodity &cm) const
    {
        return ratio > cm.ratio;
    }
    Commodity() {}
    Commodity(double p, double v) : price(p), val(v) { ratio = val / price; }
};
int main()
{
    double a, b;
    cin >> a >> b;
    while (a != -1 && b != -1)
    {
        vector<Commodity> pool;
        double x, y;
        for (int i = 0; i < b; i++)
            cin >> x >> y, pool.push_back(Commodity(y, x));
        sort(pool.begin(), pool.end());
        double cnt = 0;
        double tot = a;
        for (int i = 0; i < b; i++)
            if (tot == 0)
                break;
            else if (tot < pool[i].price)
                cnt += (tot * pool[i].ratio), tot = 0;
            else
                cnt += pool[i].val, tot -= pool[i].price;
        cout << fixed << setprecision(3) << cnt << endl;
        cin >> a >> b;
    }
    return 0;
}