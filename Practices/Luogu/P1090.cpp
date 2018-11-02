// P1090.cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int> > arr;
unsigned long long F[10002];

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int inp;
        cin >> inp;
        arr.push(inp);
    }
    int ret = 0;
    while (!arr.empty() && arr.size() != 1)
    {
        int a, b;
        a = arr.top();
        arr.pop();
        b = arr.top();
        arr.pop();
        arr.push(a + b);
        ret += a + b;
    }
    cout << ret;
    return 0;
}