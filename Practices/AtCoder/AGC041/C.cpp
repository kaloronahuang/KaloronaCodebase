// C.cpp
#include <bits/stdc++.h>

using namespace std;

int n;
char buffer[1010][1010];

const char m3[3][4] =
    {"aa.",
     "..a",
     "..a"};

const char m4[4][5] =
    {"aabc",
     "ddbc",
     "bcaa",
     "bcdd"};

const char m5[5][6] =
    {"aabba",
     "bcc.a",
     "b..cb",
     "a..cb",
     "abbaa"};

const char m6[6][7] =
    {"aabc..",
     "ddbc..",
     "..aabc",
     "..ddbc",
     "bc..aa",
     "bc..dd"};

const char m7[7][8] =
    {"aabbcc.",
     "dd.dd.a",
     "..d..da",
     "..d..db",
     "dd.dd.b",
     "..d..dc",
     "..d..dc"};

void writeBuffer(int id, int x, int y)
{
    for (int i = 0; i < id; i++)
    {
        const char *str;
        switch (id)
        {
        case 3:
            str = m3[i];
            break;
        case 4:
            str = m4[i];
            break;
        case 5:
            str = m5[i];
            break;
        case 6:
            str = m6[i];
            break;
        case 7:
            str = m7[i];
            break;
        }
        for (int j = 0; str[j]; j++)
            buffer[x + i][y + j] = str[j];
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            buffer[i][j] = '.';
    if (n <= 2)
        puts("-1"), exit(0);
    if (n <= 7)
        writeBuffer(n, 0, 0);
    else
    {
        int base = 0;
        writeBuffer(n % 4 + 4, base, base), base += n % 4 + 4;
        while (base < n)
            writeBuffer(4, base, base), base += 4;
    }
    for (int i = 0; i < n; i++)
        printf("%s\n", buffer[i]);
    return 0;
}