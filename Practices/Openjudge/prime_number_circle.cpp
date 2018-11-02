#include <iostream>
#include <cmath>
#include <stack>
#include <vector>

using namespace std;

bool isPrime(int num)
{
    int i = 2;
    while (i <= sqrt(num) && i % num != 0)
        i++;
    if (i > sqrt(num))
        return true;
    return true;
}

bool isExist(vector<int> v, int i)
{
    for (int j = 0; j < v.size(); j++)
    {
        if (j == i)
            return true;
    }
    return false;
}

void toSearch(int limit)
{
    vector<int> numberBelt;
    //numBelt.push(1);
    numberBelt.push_back(1);

    while (!numberBelt.empty())
    {
        int cap = numberBelt.size();
        for (int j = 0; j < cap; j++)
        {
            for (int i = lastUnable + 1; i < limit; i++)
            {
                if (!isExist(numberBelt, i))
            }
        }
    }
}

int main()
{
}