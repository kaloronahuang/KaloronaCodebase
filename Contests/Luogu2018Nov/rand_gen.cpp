// rand_gen.cpp
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
    srand(time(NULL));
    int n;
    cin >> n;
    cout << n << endl;
    for (int i = 0; i < n; i++)
        cout << rand() % 500 << " ";
    return 0;
}