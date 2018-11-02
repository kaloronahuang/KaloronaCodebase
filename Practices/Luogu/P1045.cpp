// P1045.cpp
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int numbox[500];

void init();

void normalize()
{
    for (int i = 0; i < 499; i++)
        numbox[i + 1] += numbox[i] / 10, numbox[i] %= 10;
    numbox[499] %= 10;
}

// num<2.1*(10^8);
void multiply(int num)
{
    for (int i = 0; i < 500; i++)
        numbox[i] *= num;
    normalize();
}

void minus1()
{
    for (int i = 0; i < 499; i++)
        if (numbox[i] == 0)
            numbox[i] = 9;
        else
        {
            numbox[i]--;
            break;
        }
}

int pow_tb[16];

void quick_pow(int time)
{
    if (time == 1)
        multiply(2);
    else if (time < 16)
        multiply(pow_tb[time]);
    else if (time % 2 == 0)
    {
        quick_pow(time / 2);
        quick_pow(time / 2);
    }
    else
    {
        quick_pow(time / 2);
        quick_pow(time / 2 + 1);
    }
}

void prep()
{
    pow_tb[0] = 1;
    for (int i = 1; i < 16; i++)
        pow_tb[i] = pow_tb[i - 1] * 2;
}

void print()
{
    for (int i = 499; i > -1; i--)
    {
        cout << numbox[i];
        if (i % 50 == 0)
            cout << endl;
    }
}

void solve()
{
    prep();
    memset(numbox, 0, sizeof(numbox));
    numbox[0] = 1;
    int time = 0;
    cin >> time;
    cout << (int)(log10(2)*time + 1) << endl;
    quick_pow(time);
    minus1();
    print();
}

int main()
{
    solve();
}