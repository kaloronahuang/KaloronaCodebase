// P1120.cpp
// Dynamic Programming;
// luogu.org
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct gcdPair
{
    int stickLength;
    int stickNum;
};

int main()
{
    // I/O;
    vector<int> sticks;
    int num;
    cin >> num;
    int total = 0;
    for (int i = 0; i < num; i++)
    {
        int current;
        cin >> current;
        if (current <= 50)
        {
            sticks.push_back(current);
            total += current;
        }
    }
    
}