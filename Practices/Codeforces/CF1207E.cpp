// CF1207E.cpp
#include <bits/stdc++.h>

using namespace std;

int main()
{
    fflush(stdout);
    cout << "? ";
    for (int i = 1; i < 100; i++)
        cout << i << " ";
    cout << 100 << endl;
    fflush(stdout);
    int ans1, ans2;
    cin >> ans1;
    fflush(stdout);
    cout << "? ";
    for (int i = 1; i < 100; i++)
        cout << (i << 7) << " ";
    cout << 12800 << endl;
    fflush(stdout);
    cin >> ans2;
    int mask1 = 0;
    for (int i = 0; i < 7; i++)
        mask1 |= (1 << i);
    int mask2 = mask1 << 7;
    cout << "! " << ((ans1 & mask2) | (ans2 & mask1)) << endl;
    return 0;
}