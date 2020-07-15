// maze.cpp
#include "grader.h"
#include <bits/stdc++.h>

int stk[20];

void findpath(int initialDeep, int T)
{
    int u = initialDeep, lastColor = 0;
    move(0);
    if (u > query())
        lastColor = 0;
    else
    {
        move(0), move(1);
        if (u > query())
            lastColor = 1;
        else
        {
            move(1), move(2);
            lastColor = 2;
        }
    }
    u--;
    while (u)
    {
        bool flag = false;
        stk[0] = lastColor;
        for (int i = 1; i <= 9; i++)
        {
            stk[i] = (stk[i - 1] + rand() % 2 + 1) % 3;
            if (move(stk[i]))
            {
                flag = true;
                break;
            }
        }
        if (flag)
            return;
        int cpos = query();
        for (int i = 9; i >= 0; i--)
        {
            if (u - i == cpos)
                break;
            move(stk[i]), cpos--;
        }
        if (u - cpos == 9)
        {
            lastColor = (stk[9] + 1) % 3;
            move(lastColor);
            if (cpos < query())
            {
                move(lastColor);
                lastColor = (lastColor + 1) % 3;
                move(lastColor);
            }
        }
        else
            move(lastColor = 3 - stk[u - cpos] - stk[u - cpos + 1]);
        u = cpos - 1;
    }
}