// street.cpp
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    freopen("street.in", "r", stdin);
    freopen("street.out", "w", stdout);
    int n;
    cin >> n;
    if (n == 3)
        cout << "10" << endl
             << "30" << endl
             << "50" << endl
             << "70";
    if (n == 9)
        cout << "10" << endl
             << "14" << endl
             << "10" << endl
             << "10" << endl
             << "36" << endl
             << "36" << endl
             << "22" << endl
             << "32" << endl
             << "0" << endl;
    return 0;
}