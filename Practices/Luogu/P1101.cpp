// P1101.cpp
// tag:DFS;
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
char map[110][110];
bool marks[110][110];
string stdrd = "yizhong";

void init()
{
    cin >> n;
    memset(marks, false, sizeof(marks));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> map[i][j];
}
// dir:
// -1 : unset
// 0 : up
// 1 : down
// 2 : right
// 3 : left
// 4 : ul
// 5 : ur
// 6 : dl
// 7 : dr
bool DFS(int posx, int posy, int cursor, int dir)
{
    if (cursor == stdrd.length() - 1 && map[posx][posy] == stdrd[cursor])
    {
        marks[posx][posy] = true;
        return true;
    }
    if (map[posx][posy] == stdrd[cursor])
    {
        bool goUp = (dir == 0) && posx > 0 && DFS(posx - 1, posy, cursor + 1, 0);
        bool goDown = (dir == 1) && posx < n - 1 && DFS(posx + 1, posy, cursor + 1, 1);
        bool goRight = (dir == 2) && posy < n - 1 && DFS(posx, posy + 1, cursor + 1, 2);
        bool goLeft = (dir == 3) && posy > 0 && DFS(posx, posy - 1, cursor + 1, 3);
        bool goUL = (dir == 4) && posx > 0 && posy > 0 && DFS(posx - 1, posy - 1, cursor + 1, 4);
        bool goUR = (dir == 5) && posx > 0 && posy < n - 1 && DFS(posx - 1, posy + 1, cursor + 1, 5);
        bool goDL = (dir == 6) && posx < n - 1 && posy > 0 && DFS(posx + 1, posy - 1, cursor + 1, 6);
        bool goDR = (dir == 7) && posx < n - 1 && posy < n - 1 && DFS(posx + 1, posy + 1, cursor + 1, 7);
        if (goUp || goDown || goRight || goLeft || goUL || goUR || goDL || goDR)
        {
            marks[posx][posy] = true;
            return true;
        }
    }
}

void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << ((marks[i][j]) ? ((char)map[i][j]) : '*');
        cout << endl;
    }
}

int main()
{
    init();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int dir = 0; dir <= 7; dir++)
                DFS(i, j, 0, dir);
    print();
    return 0;
}