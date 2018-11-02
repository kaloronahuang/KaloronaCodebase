// get the bits;
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int toDecimal(string a, int bit)
{
    int cnt = 0;
    int factor = 1;
    for (int i = a.length() - 1; i > -1; i--)
    {
        cnt += (a[i] - '0') * factor;
        factor *= bit;
    }
    return cnt;
}

int getBiggest(string a, string b, string c)
{
    string all = a + b + c;
    int biggest = 0;
    for (int i = all.length() - 1; i > -1; i--)
    {
        biggest = max(all[i] - '0', biggest);
    }
    return biggest;
}

int main()
{
    // I/O;
    string a, b, c;
    getline(cin, a, ' ');
    getline(cin, b, ' ');
    getline(cin, c);
    for (int i = getBiggest(a,b,c)+1; i < 17; i++)
    {
        int an, bn, cn;
        an = toDecimal(a, i);
        bn = toDecimal(b, i);
        cn = toDecimal(c, i);
        if (an * bn == cn)
        {
            cout << i;
            return 0;
        }
    }
    cout << "0";
    return 0;
} // end of file;