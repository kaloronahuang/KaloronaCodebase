// A.cpp
#include <bits/stdc++.h>

using namespace std;

int n;
string str;

int main()
{
    cin >> n >> str;
    int zeros = 0, ones = 0;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == '0')
            zeros++;
        else
            ones++;
    if (zeros != ones)
        cout << 1 << endl
             << str;
    else
        cout << 2 << endl
             << str[0] << " " << str.substr(1);
    return 0;
}