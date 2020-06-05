// C.cpp
#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;

int n, m, a, b;
vector<double> vec;

int main()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);
    if (max(n, m) <= 100)
    {
        for (int i = a; i <= a + n - 1; i++)
            for (int j = b; j <= b + m - 1; j++)
                vec.push_back(j * log(i));
        sort(vec.begin(), vec.end()), vec.push_back(0);
        int ans = 0;
        for (int i = 1, siz = vec.size(); i < siz; i++)
            ans += fabs(vec[i] - vec[i - 1]) > eps;
        printf("%d\n", ans);
    }
    else
    {
        for (int i = a; i <= a + n - 1; i++)
        {
            
        }
    }
    return 0;
}