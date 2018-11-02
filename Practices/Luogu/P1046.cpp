// P1046.cpp
#include <iostream>

using namespace std;

int arr[10];
int height;

int main()
{
    for (int i = 0; i < 10; i++)
        cin >> arr[i];
    cin >> height, height += 30;
    int ans = 0;
    for (int i = 0; i < 10; i++)
        if (arr[i] <= height)
            ++ans;
    cout << ans;
    return 0;
}