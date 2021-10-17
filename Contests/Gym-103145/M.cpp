// M.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 20;

char ln[MAX_N];
char word[10];

char pb4(int &pos)
{
    if (word[pos - 3] == 'i' && word[pos - 2] == 'o' && word[pos - 1] == 'n' && word[pos] == 'g')
    {
        pos -= 4;
        return 's';
    }
    if (word[pos - 3] == 'u' && word[pos - 2] == 'a' && word[pos - 1] == 'n' && word[pos] == 'g')
    {
        pos -= 4;
        return 'l';
    }
    if (word[pos - 3] == 'i' && word[pos - 2] == 'a' && word[pos - 1] == 'n' && word[pos] == 'g')
    {
        pos -= 4;
        return 'l';
    }
    return '?';
}

char pb3(int &pos)
{
    if (word[pos - 2] == 'u' && word[pos - 1] == 'a' && word[pos] == 'n')
    {
        pos -= 3;
        return 'r';
    }
    if (word[pos - 2] == 'o' && word[pos - 1] == 'n' && word[pos] == 'g')
    {
        pos -= 3;
        return 's';
    }
    if (word[pos - 2] == 'e' && word[pos - 1] == 'n' && word[pos] == 'g')
    {
        pos -= 3;
        return 'g';
    }
    if (word[pos - 2] == 'a' && word[pos - 1] == 'n' && word[pos] == 'g')
    {
        pos -= 3;
        return 'h';
    }
    if (word[pos - 2] == 'u' && word[pos - 1] == 'a' && word[pos] == 'i')
    {
        pos -= 3;
        return 'k';
    }
    if (word[pos - 2] == 'i' && word[pos - 1] == 'n' && word[pos] == 'g')
    {
        pos -= 3;
        return 'k';
    }
    if (word[pos - 2] == 'i' && word[pos - 1] == 'a' && word[pos] == 'o')
    {
        pos -= 3;
        return 'n';
    }
    if (word[pos - 2] == 'i' && word[pos - 1] == 'a' && word[pos] == 'n')
    {
        pos -= 3;
        return 'm';
    }
    return '?';
}

char pb2(int &pos)
{
    if (word[pos - 1] == 'i' && word[pos] == 'u')
    {
        pos -= 2;
        return 'q';
    }
    if (word[pos - 1] == 'e' && word[pos] == 'i')
    {
        pos -= 2;
        return 'w';
    }
    if (word[pos - 1] == 'u' && word[pos] == 'e')
    {
        pos -= 2;
        return 't';
    }
    if (word[pos - 1] == 'u' && word[pos] == 'n')
    {
        pos -= 2;
        return 'y';
    }
    if (word[pos - 1] == 'u' && word[pos] == 'o')
    {
        pos -= 2;
        return 'o';
    }
    if (word[pos - 1] == 'i' && word[pos] == 'e')
    {
        pos -= 2;
        return 'p';
    }
    if (word[pos - 1] == 'a' && word[pos] == 'i')
    {
        pos -= 2;
        return 'd';
    }
    if (word[pos - 1] == 'e' && word[pos] == 'n')
    {
        pos -= 2;
        return 'f';
    }
    if (word[pos - 1] == 'a' && word[pos] == 'n')
    {
        pos -= 2;
        return 'j';
    }
    if (word[pos - 1] == 'o' && word[pos] == 'u')
    {
        pos -= 2;
        return 'z';
    }
    if ((word[pos - 1] == 'i' && word[pos] == 'a') || (word[pos - 1] == 'u' && word[pos] == 'a'))
    {
        pos -= 2;
        return 'x';
    }
    if (word[pos - 1] == 'a' && word[pos] == 'o')
    {
        pos -= 2;
        return 'c';
    }
    if (word[pos - 1] == 'u' && word[pos] == 'i')
    {
        pos -= 2;
        return 'v';
    }
    if (word[pos - 1] == 'i' && word[pos] == 'n')
    {
        pos -= 2;
        return 'b';
    }
    return '?';
}

char pf2(int &pos)
{
    if (word[pos] == 's' && word[pos + 1] == 'h')
    {
        pos += 2;
        return 'u';
    }
    if (word[pos] == 'c' && word[pos + 1] == 'h')
    {
        pos += 2;
        return 'i';
    }
    if (word[pos] == 'z' && word[pos + 1] == 'h')
    {
        pos += 2;
        return 'v';
    }
    return '?';
}

pair<char, char> process()
{
    int len = strlen(word + 1);
    if (len == 1)
        return make_pair(word[1], word[1]);
    else if (len == 2)
        return make_pair(word[1], word[2]);
    else if (len == 3 && word[1] == 'a' && word[2] == 'n' && word[3] == 'g')
        return make_pair('a', 'h');
    else if (len == 3 && word[1] == 'e' && word[2] == 'n' && word[3] == 'g')
        return make_pair('e', 'g');
    else
    {
        char f, b;
        int pos = len;
        if ((b = pb4(pos)) != '?')
            word[pos + 1] = 0;
        else if ((b = pb3(pos)) != '?')
            word[pos + 1] = 0;
        else if ((b = pb2(pos)) != '?')
            word[pos + 1] = 0;
        else
            b = word[pos], word[pos] = 0;
        pos = 1, f = pf2(pos);
        if (f == '?')
            f = word[1];
        return make_pair(f, b);
    }
}

int main()
{
    while (cin.getline(ln, MAX_N))
    {
        int ptr = 0, wptr = 1;
        while (ln[ptr])
        {
            if (ln[ptr] == ' ')
            {
                word[wptr] = 0;
                pair<char, char> res = process();
                printf("%c%c ", res.first, res.second);
                wptr = 1, ptr++;
            }
            else
            {
                word[wptr] = ln[ptr];
                wptr++, ptr++;
            }
        }
        if (wptr != 1)
        {
            word[wptr] = 0;
            pair<char, char> res = process();
            printf("%c%c ", res.first, res.second);
        }
        puts("");
    }
    return 0;
}