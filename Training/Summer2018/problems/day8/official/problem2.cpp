#include <iostream>
using namespace std;

bool isPrimeNumber(int a)
{
    for (int i = 2; i < a; i++)
    {
        if (a % i == 0)
            return false;
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    int circle[n];
    circle[0] = 1;
    for (int i = 1; i < n; i++)
    {
        int prev = circle[i - 1];
        for (int j = 2;; j++)
        {
            if (isPrimeNumber(prev + j))
            {
                circle[i] = j;
                break;
            }
        }
    }
    // last;
    int prev = circle[n - 2];
    for (int j = 2;; j++)
    {
        if (isPrimeNumber(prev + j) && isPrimeNumber(1+j))
        {
            circle[n-1] = j;
            break;
        }
    }
    for(int i = 0;i<n;i++)
    {
        cout<<circle[i];
        if(i != n-1)
            cout<<" ";
    }
    return 0;
}