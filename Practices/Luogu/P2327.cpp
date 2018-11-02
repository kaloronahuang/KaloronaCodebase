// P2327.cpp
#include <iostream>

using namespace std;

int map[10100];
int b[10100];
int n;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> map[i];
    int solution_num = 0;
    bool flag = false;
    b[1] = 0;
    for (int i = 2; i <= n + 1; i++)
    {
        b[i] = map[i - 1] - b[i - 1] - b[i - 2];
        if (flag = b[i] > 1 || b[i] < 0)
            break;
    }
    if (!flag && b[n + 1] == 0)
        solution_num += 1;
    fill(b, b + 10100, 0);
    flag = false;
    b[1] = 1;
    for (int i = 2; i <= n + 1; i++)
    {
        b[i] = map[i - 1] - b[i - 1] - b[i - 2];
        if (flag = b[i] > 1 || b[i] < 0)
            break;
    }
    if (!flag && b[n + 1] == 0)
        solution_num += 1;
    cout << solution_num;
    return 0;
}