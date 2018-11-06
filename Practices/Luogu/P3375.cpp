// P3375.cpp
#include <iostream>

using namespace std;

string s1, s2;
int PMT[1000200];

void getNext()
{
    PMT[0] = -1;
    int k = -1;
    for (int i = 1; i < s2.length(); i++)
    {
        while (k != -1 && s2[k + 1] != s2[i])
            k = PMT[k];
        if (s2[k + 1] == s2[i])
            k++;
        PMT[i] = k;
    }
}

void kmp()
{
    int s1l = s1.length();
    int s2l = s2.length();
    int k = -1;
    getNext();
    for (int i = 0; i < s1l; i++)
    {
        while (k != -1 && s1[i] != s2[k + 1])
            k = PMT[k];
        if (s2[k + 1] == s1[i])
            k++;
        if (k == s2l - 1)
            i -= (s2l - 1), cout << i + 1 << endl, k = -1;
    }
}

int main()
{
    cin >> s1 >> s2;
    kmp();
    for (int i = 0; i < s2.length(); i++)
        cout << PMT[i] + 1 << " ";
    return 0;
}