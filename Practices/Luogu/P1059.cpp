// P1059.cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> arr;
    for (int i = 0; i < N; i++)
    {
        int current;
        cin >> current;
        bool toggle = false;
        for (int j = 0; j < arr.size(); j++)
            if (toggle = (arr[j] == current))
                break;
        if (!toggle)
            arr.push_back(current);
    }
    sort(arr.begin(), arr.end());
    cout << arr.size()<<endl;
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    return 0;
}