#include <iostream>

using namespace std;

int main()
{
    int num;
    cin >> num;
    while (num--)
    {
        long long a, b;
        cin >> a >> b;
        long long l = a + b;
        long long r = b - a + 1;
        if (l % 2 == 0)
            l /= 2;
        else
            r /= 2;
        l %= 9;
        r %= 9;
        cout << (l * r) % 9 << endl;
    }
}