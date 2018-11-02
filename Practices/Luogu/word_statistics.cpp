// statics on words;
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    int p, k, s;
    cin >> p >> k;
    string passage;
    for (int i = 0; i < p; i++)
    {
        string res;
        cin >> res;
        passage += res;
    }
    vector<string> dict;
    cin >> s;
    for (int x = 0; x < s; x++)
    {
        string wd;
        cin >> wd;
        dict.push_back(wd);
    }
    // dp;
    // preprocessing;
    int wordTable[passage.length()][passage.length()];
    memset(wordTable, 0, sizeof(wordTable));
    for (int x = passage.length() - 1; x > -1; x--)
        for (int y = x; y > -1; y--)
        {
            string part = passage.substr(y, x - y + 1);
            if (y != passage.length() - 1)
                wordTable[y][x] = wordTable[y + 1][x];
            for (int i = 0; i < dict.size(); i++)
                if (part.find(dict[i]) == 0)
                {
                    wordTable[y][x]++;
                    break;
                }
        }
    int dptable[passage.length() + 1][k + 1];
    memset(dptable, 0, sizeof(dptable));
    // pre for dp;
    for (int x = 1; x < passage.length() + 1; x++)
        dptable[x][0] = wordTable[0][x - 1];
    for (int x = 1; x < k + 1; x++)
        for (int y = 1; y < passage.length() + 1; y++)
        {
            int pos = y - 1;
            for (int j = x - 1; j < pos; j++)
                dptable[y][x] = max(dptable[y][x], dptable[j][x - 1] + wordTable[j][pos]);
        }
    cout << dptable[passage.length()][k] << endl;
    return 0;
}