#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

// funcs;

int wds[1000][1000];

void preprocessing(string passage, vector<string> dict)
{
    memset(wds, 0, sizeof(wds));
    for (int i = passage.length() - 1; i > -1; i--)
        for (int j = i; j > 0; j--)
        {
            string text = passage.substr(j, i - j + 1);
            wds[j-1][i] = wds[j][i];
            for (int it = 0; it < dict.size(); it++)
                if (text.find(dict[it]) == 0)
                    wds[j-1][i]++;
        }
}

int DP(string passage, int k, vector<string> dict)
{
    int table[k + 1][passage.length() + 1];
    memset(table, 0, sizeof(table));
    for (int i = 1; i < k + 1; i++)
        for (int j = 1; j < passage.length() + 1; j++) // string;
        {
            int ans = 0;
            for (int start = i; start <= j; start++)
                ans = max(ans, table[i-1][start-1] + wds[start][j-1]);
            table[i][j] = ans;
        }

    return table[k][passage.length()-1];
}

int main()
{
    vector<string> dict;
    string passage;
    int p, k, s;
    // doing I/O;
    cin >> p >> k;
    for (int i = 0; i < p; i++)
    {
        string inp;
        cin >> inp;
        passage += inp;
    }
    cin >> s;
    for (int i = 0; i < s; i++)
    {
        string inp;
        cin >> inp;
        dict.push_back(inp);
    }
    preprocessing(passage, dict);
    cout << DP(passage, k, dict);
    return 0;
}