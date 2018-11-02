// P3383.cpp
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 10000001;
int prime_num = 0;
bool isPrime[MAXN];

void getListLegacy()
{
    for (int i = 2; i < MAXN; i++)
    {
        if (!isPrime[i])
            continue;
        prime_num++;
        for (int j = i * 2; j < MAXN; j += i)
            isPrime[j] = false;
    }
}

int main()
{
    // init;
    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = false;
    isPrime[2] = true;
    getListLegacy();
    int n, m;
    cin >> n >> m;
    while (m--)
    {
        int curt;
        cin >> curt;
        cout << (isPrime[curt] ? "Yes" : "No") << endl;
    }
    return 0;
}