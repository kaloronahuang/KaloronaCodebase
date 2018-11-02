// P1068.cpp
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct pairDat
{
    int ID;
    int Score;
};

bool comp(pairDat a, pairDat b)
{
    if (a.Score == b.Score)
        return a.ID < b.ID;
    return a.Score > b.Score;
}

int main()
{
    int n, m;
    cin >> n >> m;
    pairDat paras[n];
    for (int i = 0; i < n; i++)
        cin >> paras[i].ID >> paras[i].Score;
    sort(paras, paras + n, comp);
    int standard = (int)(m * 1.5);
    cout << paras[standard - 1].Score << " ";
    int total = 0;
    for (int i = 0; i < n; total += (paras[i++].Score >= paras[standard - 1].Score) ? 1 : 0)
        ;
    cout << total << endl;
    for (int i = 0; i < total; i++)
        cout << paras[i].ID << " " << paras[i].Score << endl;
    return 0;
} // P1068.cpp