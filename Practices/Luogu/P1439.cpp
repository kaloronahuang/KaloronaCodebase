// P1439.cpp
#include <iostream>

using namespace std;

const int maxn = 100010;
int n;
int hash[maxn];
int arr[maxn];
int seq[maxn];
int cur = 0;

int main()
{
    cin >> n;
    int num;
    for (int i = 1; i <= n; i++)
        cin >> num, hash[num] = i;
    seq[0] = -1;
    for (int i = 1; i <= n; i++)
    {
        cin >> num;
        int x = hash[num];
        if (seq[cur] < x)
            seq[++cur] = x;
        else
            *(lower_bound(seq + 1, seq + 1 + cur, x)) = x;
    }
    cout << cur;
    return 0;
}