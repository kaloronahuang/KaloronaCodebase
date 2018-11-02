#include <iostream>
#include <algorithm>

using namespace std;

int tian[1010];
int king[1010];

int main()
{
    int n;
    cin >> n;
    while (n != 0)
    {
        for (int i = 0; i < n; i++)
            cin >> tian[i];
        for (int i = 0; i < n; i++)
            cin >> king[i];
        sort(tian, tian + n);
        sort(king, king + n);
        int t1 = 0;
        int p1 = 0;
        int tlast = n - 1;
        int plast = n - 1;
        int recv = 0;
        while (t1 <= tlast && p1 <= plast)
            if (tian[t1] < king[p1])
            {
                recv -= 200;
                t1++, plast--;
            }
            else if (tian[t1] > king[p1])
            {
                recv += 200;
                t1++, p1++;
            }
            else if (tian[tlast] < king[plast])
            {
                recv -= 200;
                t1++, plast--;
            }
            else if (tian[tlast] > king[plast])
            {
                recv += 200;
                tlast--, plast--;
            }
            else if (tian[t1] < king[plast])
            {
                recv -= 200;
                t1++, plast--;
            }
            else
                break;
        cout << recv << endl;
        cin >> n;
    }
    return 0;
}