// D.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 501000;
string A, B;
int totA, totB, nxt[MAX_N];
void getNext(string str)
{
    string tmp = " " + str;
    for (int i = 2; i <= tmp.length() - 1; i++)
    {
        int j = nxt[i - 1];
        while (j && tmp[j + 1] != tmp[i])
            j = nxt[j];
        if (tmp[j + 1] == tmp[i])
            nxt[i] = j + 1;
        else
            nxt[i] = 0;
    }
}
int main()
{
    cin >> A >> B;
    getNext(B);
    for (int i = 0; i < A.length(); i++)
        totA += A[i] - '0';
    for (int i = 0; i < B.length(); i++)
        totB += B[i] - '0';
    if (A.length() < B.length() || totA < totB)
        cout << A, exit(0);
    A = " " + A, B = " " + B;
    int ans = A.length();
    for (int i = 1, j = 0; i < A.length(); i++)
    {
        if (totA && B[j + 1] == '1')
            totA--, A[i] = '1', j++;
        else if (B[j + 1] == '0')
            A[i] = '0', j++;
        else
        {
            ans = i;
            break;
        }
        if (j == B.length() - 1)
            j = nxt[j];
    }
    for (int i = ans; i < A.length(); i++)
        A[i] = '0';
    while (totA)
    {
        ans--;
        if (A[ans] == '1')
            totA++;
        A[ans] = '1', totA--;
    }
    cout << A.substr(1);
    return 0;
}