// P2730.cpp
#include <bits/stdc++.h>

using namespace std;

map<string, string> ump;
string dst;

string opA(string target)
{
    for (int i = 0; i < 4; i++)
        swap(target[i], target[7 - i]);
    return target;
}

string opB(string target)
{
    string ret = target;
    ret[0] = target[3], ret[1] = target[0], ret[2] = target[1], ret[3] = target[2];
    ret[4] = target[5], ret[5] = target[6], ret[6] = target[7], ret[7] = target[4];
    return ret;
}

string opC(string target)
{
    string ret = target;
    ret[1] = target[6], ret[2] = target[1], ret[5] = target[2], ret[6] = target[5];
    return ret;
}

void bfs()
{
    queue<string> q;
    q.push("12345678"), ump["12345678"] = "";
    while (!q.empty())
    {
        string u = q.front();
        q.pop();
        string A = opA(u), B = opB(u), C = opC(u);
        if (ump.count(A) == 0)
            ump[A] = ump[u] + 'A', q.push(A);
        if (ump.count(B) == 0)
            ump[B] = ump[u] + 'B', q.push(B);
        if (ump.count(C) == 0)
            ump[C] = ump[u] + 'C', q.push(C);
        if (ump.count(dst) != 0)
        {
            cout << ump[dst].length() << endl
                 << ump[dst];
            exit(0);
        }
    }
}

int main()
{
    dst = "";
    for (int i = 1, tmp; i <= 8; i++)
        scanf("%d", &tmp), dst += char('0' + tmp);
    bfs();
    return 0;
}