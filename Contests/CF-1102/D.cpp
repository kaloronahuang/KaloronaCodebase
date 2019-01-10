// D.cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
struct node
{
    int num;
    char ch;
    bool operator<(const node &nd) { return num < nd.num; }
} arr[255];
string str;
int main()
{
    int siz;
    cin >> siz >> str;
    arr[0].ch = '0', arr[1].ch = '1', arr[2].ch = '2';
    for (int i = 0; i < siz; i++)
        arr[str[i] - '0'].num++, arr[str[i] - '0'].ch = str[i];
    sort(arr, arr + 3);
    int avg = siz / 3;
    if (abs(avg - arr[0].num) < abs(avg - arr[2].num))
        swap(arr[0], arr[2]);
    if (arr[1].ch < arr[0].ch)
        swap(arr[1], arr[0]);
    int nk = 0, nd = 0;
    for (int i = siz - 1; i >= 0; i--)
        if (str[i] == arr[2].ch)
        {
            if (nk < abs(arr[1].num - avg))
                nk++, str[i] = arr[1].ch;
            else if (nd < abs(arr[0].num - avg))
                nd++, str[i] = arr[0].ch;
        }
    cout << str;
    return 0;
}