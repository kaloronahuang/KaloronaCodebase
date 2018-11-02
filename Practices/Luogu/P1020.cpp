// P1020.cpp
// Eg Inp:389 207 155 300 299 170 158 65 -1
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

vector<int> seq;
int n;

bool cmp(int a, int b)
{
    return a > b;
}

void init()
{
    seq.push_back(0);
    int num;
    while (scanf("%d", &num) != EOF)
        seq.push_back(num);
    n = seq.size();
}

void solve()
{
    int ansa = 1;
    int ansb = 1;
    int seqa[n + 1];
    int seqb[n + 1];
    seqa[1] = seq[1], seqb[1] = seq[1];
    // LCS;
    for (int i = 2; i < n + 1; i++)
        if (seq[i] <= seqa[ansa])
            seqa[++ansa] = seq[i];
        else
        {
            int index = upper_bound(seqa + 1, seqa + ansa, seq[i], cmp) - seqa;
            seqa[index] = seq[i];
        }
    // LIS;
    for (int i = 1; i < n + 1; i++)
        if (seq[i] > seqb[ansb])
            seqb[++ansb] = seq[i];
        else
        {
            int index = lower_bound(seqb + 1, seqb + ansb, seq[i]) - seqb;
            seqb[index] = seq[i];
        }
    cout << ansa - 1 << endl
         << ansb;
}

int main()
{
    init();
    solve();
}