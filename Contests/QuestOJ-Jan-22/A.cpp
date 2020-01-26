// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;
// typedef pair<int, int> pii;

char Str[2][MAX_N];
int n, m, limit, cntA[2], cntB[2];

namespace Subtask1
{

int calc()
{
    int ret = 0;
    for (int xlen = 1; xlen <= limit; xlen++)
        for (int X = 0; X < (1 << xlen); X++)
            for (int ylen = 1; ylen <= limit; ylen++)
                for (int Y = 0; Y < (1 << ylen); Y++)
                {
                    string S, T, X_str, Y_str;
                    for (int i = 0; i < xlen; i++)
                        X_str += (((X >> i) & 1) + '0');
                    for (int i = 0; i < ylen; i++)
                        Y_str += (((Y >> i) & 1) + '0');
                    for (int i = 1; i <= n; i++)
                        if (Str[0][i] == 'A')
                            S += X_str;
                        else
                            S += Y_str;
                    for (int i = 1; i <= m; i++)
                        if (Str[1][i] == 'A')
                            T += X_str;
                        else
                            T += Y_str;
                    if (S == T)
                        ret++;
                }
    return ret;
}

void subtask1Handler()
{
    vector<int> Svec, Tvec;
    for (int i = 1; i <= n; i++)
        if (Str[0][i] == '?')
            Svec.push_back(i);
    for (int i = 1; i <= m; i++)
        if (Str[1][i] == '?')
            Tvec.push_back(i);
    int ans = 0;
    for (int statS = 0, sizS = Svec.size(); statS < (1 << sizS); statS++)
        for (int statT = 0, sizT = Tvec.size(); statT < (1 << sizT); statT++)
        {
            for (int i = 0; i < sizS; i++)
                Str[0][Svec[i]] = ((statS >> i) & 1) + 'A';
            for (int i = 0; i < sizT; i++)
                Str[1][Tvec[i]] = ((statT >> i) & 1) + 'A';
            ans += calc();
        }
    printf("%d\n", ans);
}

} // namespace Subtask1

int main()
{
    scanf("%s%s%d", Str[0] + 1, Str[1] + 1, &limit);
    n = strlen(Str[0] + 1), m = strlen(Str[1] + 1);
    Subtask1::subtask1Handler();
    return 0;
}