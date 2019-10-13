// P1039.cpp
#include <bits/stdc++.h>

using namespace std;

const string weather[8] = {
    "lrzx sxbk",
    "Today is Sunday.",
    "Today is Monday.",
    "Today is Tuesday.",
    "Today is Wednesday.",
    "Today is Thursday.",
    "Today is Friday.",
    "Today is Saturday.",
};

int n, m, p, froms[330], fake[30], ansId;
bool err;
string names[30], citations[330];

void set_stat(int pid, int stat)
{
    if (fake[pid] && fake[pid] != stat)
        err = true;
    else
        fake[pid] = stat;
}

int main()
{
    cin >> m >> n >> p;
    for (int i = 1; i <= m; i++)
        cin >> names[i];
    for (int i = 1; i <= p; i++)
    {
        string from;
        cin >> from, from.erase(from.end() - 1);
        for (int id = 1; id <= m; id++)
            if (names[id] == from)
                froms[i] = id;
        getline(cin, citations[i]);
        citations[i].erase(citations[i].begin());
        citations[i].erase(citations[i].end() - 1);
    }

    for (int week = 1; week <= 7; week++)
        for (int gulityId = 1; gulityId <= m; gulityId++)
        {
            err = false, memset(fake, 0, sizeof(fake));
            for (int i = 1; i <= p; i++)
            {
                int from = froms[i];
                if (citations[i] == "I am guilty.")
                    set_stat(from, gulityId == from ? 1 : -1);
                if (citations[i] == "I am not guilty.")
                    set_stat(from, gulityId != from ? 1 : -1);

                for (int j = 1; j <= 7; j++)
                    if (citations[i] == weather[j])
                        set_stat(from, j == week ? 1 : -1);

                for (int j = 1; j <= m; j++)
                {
                    if (citations[i] == names[j] + " is guilty.")
                        set_stat(from, j == gulityId ? 1 : -1);
                    if (citations[i] == names[j] + " is not guilty.")
                        set_stat(from, j != gulityId ? 1 : -1);
                }
            }
            int cnt = 0, not_determinated = 0;
            for (int i = 1; i <= m; i++)
                cnt += fake[i] == -1, not_determinated += fake[i] == 0;
            if (!err && cnt <= n && cnt + not_determinated >= n)
                if (ansId != 0 && ansId != gulityId)
                    puts("Cannot Determine"), exit(0);
                else
                    ansId = gulityId;
        }
    if (ansId == 0)
        cout << "Impossible";
    else
        cout << names[ansId];
    return 0;
}