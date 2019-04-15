// C.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3e5 + 2000;
int len, n;
char str[MAX_N];
void goFuck()
{
    printf(":("), exit(0);
}
int main()
{
    scanf("%d", &len), scanf("%s", str), n = len;
    int remL = 0, remR = 0;
    if ((len & 1) || ((len - 2) & 1) || str[0] == ')' || str[len - 1] == '(')
        goFuck();
    str[0] = '(', str[len - 1] = ')';
    len -= 2;
    for (int i = 1; i < n - 1; i++)
        if (str[i] == '(')
            remL++;
        else if (str[i] == ')')
            remR++;
    remL = len / 2 - remL, remR = len / 2 - remR;
    for (int i = 1; i < n - 1; i++)
        if (str[i] == '?' && remL)
            str[i] = '(', remL--;
        else if (str[i] == '?' && remR)
            str[i] = ')', remR--;
    if (remL || remR)
        goFuck();
    int tot = 0;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '(')
            tot++;
        else
            tot--;
        if (tot == 0 && i != n - 1)
            goFuck();
    }
    if (tot != 0)
        goFuck();
    cout << str;
    return 0;
}