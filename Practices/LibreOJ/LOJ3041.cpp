// LOJ3041.cpp
#include <bits/stdc++.h>
#include "minerals.h"

/*
int query(int);
void answer(int, int);
*/

using namespace std;

const double coeff = 0.38;

int last_color = 0;
vector<int> pts[2];

void solve(vector<int> pt1, vector<int> pt2, int light)
{
    if (pt1.size() == 0)
        return;
    if (pt1.size() == 1)
        return (void)(Answer(pt1.front(), pt2.front()));
    vector<int> res[2][2];
    int len = pt1.size(), mid = ceil(coeff * len);
    for (int i = 0; i < mid; i++)
        last_color = Query(pt1[i]), res[0][0].push_back(pt1[i]);
    for (int i = mid; i < len; i++)
        res[1][0].push_back(pt1[i]);
    for (int i = 0; i < len; i++)
    {
        if (res[0][0].size() == res[0][1].size())
            res[1][1].push_back(pt2[i]);
        else if (res[1][0].size() == res[1][1].size())
            res[0][1].push_back(pt2[i]);
        else
        {
            int u = Query(pt2[i]);
            if ((u != last_color) ^ light)
                res[0][1].push_back(pt2[i]);
            else
                res[1][1].push_back(pt2[i]);
            last_color = u;
        }
    }
    solve(res[0][0], res[0][1], light ^ 1), solve(res[1][0], res[1][1], light);
}

void Solve(int N)
{
    for (int i = 1; i <= (N << 1); i++)
    {
        int u = Query(i);
        if (last_color == u)
            pts[1].push_back(i);
        else
            pts[0].push_back(i);
        last_color = u;
    }
    solve(pts[0], pts[1], 0);
}