// F.cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
string a, b;
int dplen[3100][3100], lena, lenb;
short ldp[3100][3100], rdp[3100][3100];
int main()
{
    cin >> a >> b;
    if (a.length() < b.length())
        swap(a, b);
    lena = a.length(), lenb = b.length();
    a = ' ' + a, b = ' ' + b;
    for (int i = 1; i <= lena; i++)
        for (int j = 1; j <= lenb; j++)
            if (a[i] == b[j])
            {
                dplen[i][j] = dplen[i - 1][j - 1] + 1;
                ldp[i][j] = i, rdp[i][j] = j;
            }
            else
            {
                if (dplen[i][j - 1] > dplen[i - 1][j])
                    dplen[i][j] = dplen[i][j - 1],
                    ldp[i][j] = ldp[i][j - 1], rdp[i][j] = rdp[i][j - 1];
                else
                    dplen[i][j] = dplen[i - 1][j],
                    ldp[i][j] = ldp[i - 1][j], rdp[i][j] = rdp[i - 1][j];
            }
    string str;
    for (int x = ldp[lena][lenb], y = rdp[lena][lenb]; x != 0;)
    {
        str += a[x];
        int x_ = x;
        x = ldp[x - 1][y - 1], y = rdp[x_ - 1][y - 1];
    }
    reverse(str.begin(), str.end());
    cout << str;
    return 0;
}