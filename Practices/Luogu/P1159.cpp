// P1159.cpp
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 200;
queue<string> up;
queue<string> down;
bool same[maxn];
string strs[maxn];
int n;

int main()
{
    fill(same, same + maxn, false);
    cin >> n;
    string opt;
    for (int i = 1; i <= n; i++)
    {
        cin >> strs[i] >> opt;
        if (opt == "UP")
            up.push(strs[i]);
        else if (opt == "SAME")
            same[i] = true;
        else
            down.push(strs[i]);
    }
    for (int i = 1; i <= n; i++)
        if (same[i])
            cout << strs[i] << endl;
        else if (!down.empty())
            cout << down.front() << endl, down.pop();
        else
            cout << up.front() << endl, up.pop();
    return 0;
}