// A.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool arr1[255], arr2[255];
string key, tmp;
int main()
{
    cin >> key;
    for (int i = 1; i <= 5; i++)
        cin >> tmp, arr1[tmp[0]] = true, arr2[tmp[1]] = true;
    printf(arr1[key[0]] || arr2[key[1]] ? "YES" : "NO");
    return 0;
}