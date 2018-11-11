// fib.cpp
#include <iostream>

using namespace std;

#define ll long long
const int maxn = 0xAC666;
int fib[maxn];
int mod;

int main()
{
    cin >> mod;
    fib[0] = 1;
    fib[1] = 1;
    bool flag = true;
    int dt = 0;
    for (int i = 2; i < mod * 9; i++)
    {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
        if (fib[i] == 1 && fib[i - 1] == 0)
        {
            flag = false, dt = i;
            break;
        }
    }
    cout << dt << endl;
    return 0;
}