// ARC097A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5000;

int n, k;
string str;

int main()
{
    cin >> str >> k;
    vector<string> vec;
    for (int i = 0; i < str.length(); i++)
        for (int j = 1; j <= min(k, int(str.length() - i)); j++)
            vec.push_back(str.substr(i, j));
    sort(vec.begin(), vec.end()), vec.erase(unique(vec.begin(), vec.end()), vec.end());
    cout << vec[k - 1] << endl;
    return 0;
}