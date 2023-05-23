// J.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20020;

int T, ans[2];
char state[10], codebox[10];
map<int, pair<int, int>> result_tab;

int map_to_code(char x)
{
    switch (x)
    {
    case '.':
        return 0;
    case 'X':
        return 1;
    case 'O':
        return 2;
    }
}

char code_to_map(int x)
{
    switch (x)
    {
    case 0:
        return '.';
    case 1:
        return 'X';
    case 2:
        return 'O';
    }
}

int encode()
{
    int ret = 0;
    for (int i = 0; i < 9; i++)
        ret = 3 * ret + map_to_code(codebox[i]);
    return ret;
}

void decode(int x)
{
    for (int i = 8; i >= 0; i--)
        codebox[i] = code_to_map(x % 3), x /= 3;
}

char check()
{
    // rows;
    bool marks[2];
    marks[0] = marks[1] = false;
    for (int i = 0; i < 3; i++)
    {
        if (codebox[i * 3] == '.')
            continue;
        bool lflag = true;
        for (int j = 1; j < 3; j++)
            lflag &= (codebox[i * 3] == codebox[i * 3 + j]);
        if (lflag)
            marks[codebox[i * 3] == 'O'] = true;
    }
    // cols;
    for (int j = 0; j < 3; j++)
    {
        if (codebox[j] == '.')
            continue;
        bool lflag = true;
        for (int i = 1; i < 3; i++)
            lflag &= (codebox[j] == codebox[i * 3 + j]);
        if (lflag)
            marks[codebox[j] == 'O'] = true;
    }
    // diag;
    if (codebox[0] != '.' && codebox[4] == codebox[0] && codebox[8] == codebox[0])
        marks[codebox[0] == 'O'] = true;
    if (codebox[2] != '.' && codebox[4] == codebox[2] && codebox[6] == codebox[2])
        marks[codebox[2] == 'O'] = true;
    if (marks[0] && marks[1])
        return '!';
    else if (!(marks[0] || marks[1]))
        return '.';
    else
        return marks[1] ? 'O' : 'X';
}

// <X, O>

void dfs(int s, int hand)
{
    // checker;
    decode(s);
    char res = check();
    if (res == 'X' || res == 'O')
    {
        result_tab[s] = (res == 'O' ? make_pair(0, 1) : make_pair(1, 0));
        return;
    }
    result_tab[s] = make_pair(0, 0);
    for (int i = 0; i < 9; i++)
        if (codebox[i] == '.')
        {
            int nxt = 0;
            if (hand == 0)
                codebox[i] = 'X';
            else
                codebox[i] = 'O';
            nxt = encode();
            dfs(nxt, hand ^ 1);
            result_tab[s].first += result_tab[nxt].first;
            result_tab[s].second += result_tab[nxt].second;
            // recover;
            decode(s);
            codebox[i] = '.';
        }
}

int main()
{
    strcpy(codebox, ".........");
    dfs(encode(), 0);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", state), strcpy(codebox, state);
        int s = encode();
        if (result_tab.count(s) == 0)
            printf("%d %d\n", -1, -1);
        else
            printf("%d %d\n", result_tab[s].first, result_tab[s].second);
    }
    return 0;
}
